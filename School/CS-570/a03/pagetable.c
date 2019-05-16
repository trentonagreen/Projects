#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pagetable.h"

/*
  Contruct the pagetable.
  Takes in a
    level count, bitmask array, shift array, entry count array, and tablesize
  Add up size of pagetable
*/
struct pagetable* construct_pt(
  int ex_level_count, 
  int ex_bitmask_arr[], 
  int ex_shift_arr[], 
  int ex_entry_count[],
  int ex_table_size) {
  pagetable *pt = (pagetable*)malloc(sizeof(pagetable));

  pt->level_count = ex_level_count;
  pt->bitmask_arr = ex_bitmask_arr;
  pt->shift_arr = ex_shift_arr;
  pt->entry_count = ex_entry_count;
  pt->root_level_ptr = NULL;
  pt->table_size = ex_table_size;

  pt->table_size = pt->table_size + sizeof(pt->level_count);
  pt->table_size = pt->table_size + sizeof(pt->bitmask_arr);
  pt->table_size = pt->table_size + sizeof(pt->shift_arr);
  pt->table_size = pt->table_size + sizeof(pt->entry_count);

  return pt;
}

/*
  Construct the level 0 of the pagetable.
  Allocate memory for the level and it's next level array.
  Add up size of the level zero and its array
*/
void contruct_lvl_zero(pagetable *pt) {
  level *lvl_zero = (level*)malloc(sizeof(level));

  lvl_zero->depth = 0;
  lvl_zero->pagetable_ptr = pt;

  // Allocate memory for the dynamic array from level struct
  lvl_zero->next_level_arr = (level*)malloc(sizeof(level) * pt->entry_count[0]);
  
  // Set all pointers to NULL
  for(int i = 0; i < pt->entry_count[0]; i++) {
    lvl_zero->next_level_arr[i].next_level_ptr = NULL;
  }
  lvl_zero->map_arr = NULL;
  pt->root_level_ptr = lvl_zero;

  // Add up size of level and its array to table size
  int lvl_size = sizeof(lvl_zero->next_level_arr); 
  int lvl_arr_size = lvl_size * pt->entry_count[0];
  lvl_size = lvl_size + lvl_arr_size;

  pt->table_size = pt->table_size + sizeof(lvl_zero);
  pt->table_size = pt->table_size + sizeof(lvl_zero->depth);
  pt->table_size = pt->table_size + sizeof(lvl_zero->pagetable_ptr);
  pt->table_size = pt->table_size + lvl_size;
  pt->table_size = pt->table_size + sizeof(pt->root_level_ptr);
  pt->table_size = pt->table_size + sizeof(lvl_zero->map_arr);
}

/*
  Insert a level into the pagetable.
  If the level depth is the last level create leaf and call LeafLevel.
  If the next level array is already allocated insert for next page entry.
  Else allocate memory for new level and for next level array.
  Add up sizes of the level and the next level array.
*/
void PageInsertLevel(level *lvl, 
                    unsigned int logical_addr, 
                    unsigned int frame) {

  unsigned int idx = LogicalToPage(logical_addr, 
                                   lvl->pagetable_ptr->bitmask_arr[lvl->depth], 
                                   lvl->pagetable_ptr->shift_arr[lvl->depth]);

  // If on the last level, it is a leaf
  if(lvl->depth == lvl->pagetable_ptr->level_count - 1) {
    LeafLevel(lvl, logical_addr, frame);
  }

  // if the next level already exists go into it
  else if(lvl->next_level_arr[idx].next_level_ptr != NULL) {
    level *new_lvl = lvl->next_level_arr[idx].next_level_ptr;
    PageInsertLevel(new_lvl, logical_addr, frame);
  }

  // allocate memory for next level and it's array
  else {  
    level *new_lvl = (struct level*)malloc(sizeof(level));

    new_lvl->depth = lvl->depth + 1;
    new_lvl->pagetable_ptr = lvl->pagetable_ptr;

    // Allocate memory for the dynamic array from level struct
    new_lvl->next_level_arr = (level*)malloc(sizeof(level) * 
                          new_lvl->pagetable_ptr->entry_count[new_lvl->depth]);
    
    // Set all pointers to NULL
    for(int i=0; i<new_lvl->pagetable_ptr->entry_count[new_lvl->depth]; i++) {
      new_lvl->next_level_arr[i].next_level_ptr = NULL;
    }
    lvl->next_level_arr[idx].next_level_ptr = new_lvl;
    lvl->map_arr = NULL;

    int lvl_size = sizeof(new_lvl->next_level_arr);
    int lvl_arr_size = lvl_size*lvl->pagetable_ptr->entry_count[new_lvl->depth];
    lvl_size = lvl_size + lvl_arr_size;

    lvl->pagetable_ptr->table_size = lvl->pagetable_ptr->table_size
                                     + sizeof(new_lvl);
    lvl->pagetable_ptr->table_size = lvl->pagetable_ptr->table_size
                                     + sizeof(new_lvl->depth);
    lvl->pagetable_ptr->table_size = lvl->pagetable_ptr->table_size
                                     + sizeof(new_lvl->pagetable_ptr);
    lvl->pagetable_ptr->table_size = lvl->pagetable_ptr->table_size
                                     + lvl_size;
    lvl->pagetable_ptr->table_size = lvl->pagetable_ptr->table_size
                                     + sizeof(new_lvl->map_arr);

    PageInsertLevel(new_lvl, logical_addr, frame);
  }
}

/*
  Called if the page inserted is in the last level depth.
  Checks to see if the map array was created, and creates one if it wasn't
  Set all values in map array to invalid.
  But set value of page entry in map to valid and assign frame.
  Add up size of map array
*/
void LeafLevel(level *lvl, unsigned int logical_addr, int frame) {
  pagetable *pt = lvl->pagetable_ptr;
  unsigned int idx = LogicalToPage(logical_addr, 
                                   pt->bitmask_arr[lvl->depth], 
                                   pt->shift_arr[lvl->depth]);

  // check if map already created
  if(lvl->map_arr != NULL) {
    if(lvl->map_arr[idx].isValid == -1) {
      lvl->map_arr[idx].isValid = 1;
      lvl->map_arr[idx].frame = frame; 
    }
  }

  // create map
  else {
    // allocate memory for map
    lvl->map_arr = (map*)malloc(
                    sizeof(map) * lvl->pagetable_ptr->entry_count[lvl->depth]);

    // set all values of isValid to -1
    for(int i = 0; i < lvl->pagetable_ptr->entry_count[lvl->depth]; i++) {
      lvl->map_arr[i].isValid = -1;
    }

    // for this page entry set to valid and assign frame
    lvl->map_arr[idx].isValid = 1;
    lvl->map_arr[idx].frame = frame;

    // add up tablesize
    int map_size = sizeof(lvl->map_arr);
    int map_arr_size = map_size * sizeof(pt->entry_count[lvl->depth]);
    pt->table_size = pt->table_size + map_arr_size;
    pt->table_size = pt->table_size + sizeof(lvl->map_arr->isValid);
    pt->table_size = pt->table_size + sizeof(lvl->map_arr->frame);
  }
}

/*  
  Given a logical address, mask and shift...
  Create the page entry for the array.
  Apply mask and shift.
*/
unsigned int LogicalToPage(unsigned int logical_addr, 
                           unsigned int mask, 
                           unsigned int shift) {
  unsigned int idx = 0;
  idx = logical_addr & mask;
  idx = idx >> shift;

  return idx;
}

/*
  Checks if logical address entry page is in the pagetable.
  Traverses through the tree to get to the map array
  If map array is null, return null.
  If the map array exists and the location is valid
    return the map array
*/
struct map* PageLookup(struct pagetable *pt, unsigned int logical_address) {
  level *lvl = pt->root_level_ptr;

  unsigned int idx = 0;
  for(int i = 0; i < pt->level_count; i++) {
    idx = LogicalToPage(logical_address, pt->bitmask_arr[i], pt->shift_arr[i]);

    if(lvl->map_arr != NULL) {
      if(lvl->map_arr[idx].isValid == 1) {
        return lvl->map_arr;
      }
    }

    if(lvl->next_level_arr[idx].next_level_ptr == NULL) {
     return NULL;
    }
    lvl = lvl->next_level_arr[idx].next_level_ptr;
  }

  return NULL;
}

/*
  Calculate the contents to place into the pagetable
  Calls
    CalculateMask
    CalculateShift
    CalculateEntry
*/
void CalculatePagetableContents(int level_count, 
                                int bitmask_arr[], 
                                int shift_arr[], 
                                int entry_count[]) {
  CalculateEntry(entry_count, level_count);
  CalculateShift(shift_arr, level_count);
  CalculateMask(bitmask_arr, level_count);

}

/*
  Calculates the entry count given the number of bits
  2 ^ nth number of bits
  ex - input of 4 4 8
  2 ^ 4 = 16, entry_count[0] = 16
*/
void CalculateEntry(int* entry_count, int level_count) {
  for(int i = 0; i < level_count; i++) {
    int entry = 1;
    for(int j = 0; j < entry_count[i]; j++) {
      entry = 2 * entry;
    }
    entry_count[i] = entry;
  }
}

/*
  Calculates the shift array given the number of bits
  ex - input 4 4 8
  32 - 4 = 28... 24... 12
*/
void CalculateShift(int* shift_arr, int level_count) {
  int shift = 32;
  for(int i = 0; i < level_count; i++) {
    shift = shift - shift_arr[i];
    shift_arr[i] = shift;
  }
}

/*
  Calculates the bitmask array given the bits
  Create the mask and shift to the corresponding location in 32 bit int
  ex - input 4 4 8
  F0000000, 0F000000, 00FF0000
*/
void CalculateMask(int* bitmask_arr, int level_count) {
  int mask = 0;
  int shift = 32;

  for(int i = 0; i < level_count; i++) {
    shift = shift - bitmask_arr[i];

    mask = (1 << bitmask_arr[i]) - 1;
    mask = mask << shift;

    bitmask_arr[i] = mask;
  }
}

/*
  Prints the page entry and the corresponding frame allocated for it.
  Traverses through the tree to the map.
  If the page entry in the map isValid then print the entry and frame
*/
void PrintPageToFrame(pagetable *pt,
                      map* m, 
                      unsigned int logical_addr, 
                      int total_numbers, 
                      FILE *out) {

  level *lvl = pt->root_level_ptr;

  unsigned int idx = 0;
  for(int i = 0; i < pt->level_count; i++) {
    idx = LogicalToPage(logical_addr, pt->bitmask_arr[i], pt->shift_arr[i]);

    if(lvl->map_arr != NULL) {
      if(lvl->map_arr[idx].isValid == 1) {
        logical_addr = logical_addr >> (32 - total_numbers);
        fprintf(out, "%08X -> %08X\n",logical_addr, lvl->map_arr[idx].frame);
      }
    }
    lvl = lvl->next_level_arr[idx].next_level_ptr;
  }
}

/*
  Prints the logical address and the corresponding physical address
*/
void PrintLogicalToPhysical(unsigned int logical_addr, unsigned int phys_addr){
  printf("%08X -> %08X\n", logical_addr, phys_addr);
}

/*
  Given a given a pagetable, logical address, offset and total number of bits, 
    finds the physical address.
  Traverses through the tree to fthe map.
  Once found a valid map, find the page size, to find the base address.
  Upon finding add to offset to find physical address
*/
unsigned int FindPhysicalAddress(pagetable* pt,   
                                 unsigned int logical_addr, 
                                 unsigned int offset, 
                                 unsigned int total_number) {
  level *lvl = pt->root_level_ptr;
  map *ex_map;

  unsigned int idx = 0;
  for(int i = 0; i < pt->level_count; i++) {
    idx = LogicalToPage(logical_addr, pt->bitmask_arr[i], pt->shift_arr[i]);

    if(lvl->map_arr != NULL) {
      if(lvl->map_arr[idx].isValid == 1) {
        ex_map = lvl->map_arr;
      }
    }
    lvl = lvl->next_level_arr[idx].next_level_ptr;
  }

  unsigned int page_size = 32 - total_number;
  unsigned int base_addr = ex_map[idx].frame * page_size;
  unsigned int phys_addr = base_addr + offset;
  return phys_addr;
}

/*
  Finds the offset of a given logical address.
  Create offset mask from the bitmask array.
  Apply mask to logical address.
*/
unsigned int FindOffset(pagetable *pt, unsigned int logical_addr) {

  unsigned int idx = LogicalToPage(logical_addr, 
                                   pt->bitmask_arr[pt->level_count-1], 
                                   pt->shift_arr[pt->level_count-1]);

  int bits = 0;
  for(int i = 0; i < pt->level_count; i++) {
    bits = bits + Count1Bits(pt->bitmask_arr[i]);
  }

  int offset = 0;
  bits = 32 - bits;
  offset = (1 << bits) - 1;
  offset = offset & logical_addr;

  return offset;
}

/*
  Determines if the char* is a number
*/
int isNumber(char number[]) {
  for(int i = 0; number[i] != 0; i++) {
    if(!isdigit(number[i])) {
      return -1;
    }
  }
  return 1;
}

/*
  Counts the number of 1 bits from a given number.
*/
unsigned int Count1Bits(unsigned int n) { 
  unsigned int count = 0; 
  while (n) { 
    count += n & 1; 
    n >>= 1; 
  } 
  return count; 
} 

/*
  Free the pagetable
*/
void FreePagetable(struct pagetable* pt) {
  level *lvl = pt->root_level_ptr;

  //traverse through and start freeing from leaf level
  for(int i = 0; i < pt->entry_count[i]; i++) {
    if(lvl->next_level_arr[i].next_level_ptr != NULL) {
      lvl = lvl->next_level_arr[i].next_level_ptr;
    }
    if(lvl->map_arr != NULL) {
      free(lvl->next_level_arr[i].next_level_ptr);
    }
  }
  free(pt);
}