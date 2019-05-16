#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "pagetable.h"
#include "byutr.h"

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("NOT ENOUGH ARGS\n");
    return 0;
  }

  FILE *trace_fp;               // File to read addresses from
  FILE *out;                    // File for p flag to print out to
  unsigned long i;              // Number of addresses
  p2AddrTr trace;               // Address

  unsigned int N = 0;           // Number of address to read for n flag
  int isN = FALSE;              // n flag boolean
  int t = FALSE;                // t flag boolean
  int p = FALSE;                // p flag boolean
  int level_count = 0;          // Number of levels for pagetable
  int tot_num = 0;              // Total number of bits from input
  int numbers[argc];            // Number array to hold valid number from input
  int char_is_int;              // Number when input is a number
  int frame = 0;                // Frame
  int hit = 0;                  // Hits
  int miss = 0;                 // Misses

  map *m;                       // Map for PageLookup return

  unsigned int offset = 0;      // Offset
  unsigned int phys_addr = 0;   // Physical Address
  unsigned int page_size = 1;   // Page Size
  unsigned int logical_addr;    // Logical Address
  
  //Handle args
  for(int i = 0; i < argc; i++) {

    // If input is a n flag set isN to true and convert arg after to int
    if(strcmp(argv[i], "-n") == 0 && argv[i+1] != NULL) {
      i = i + 1;
      N = atoi(argv[i]);
      isN = TRUE;
    }

    // If input is p flag set p to true and next arg is file to open
    else if(strcmp(argv[i], "-p") == 0 && argv[i+1] != NULL) {
      p = TRUE;
      i = i + 1;
      out = fopen(argv[i], "w");
    }

    // If input is t flag set t to true
    else if(strcmp(argv[i], "-t") == 0) {
      t = TRUE;
    }
    
    // Checks if any other input is a number and if it is store it
    else if(isNumber(argv[i]) == 1) {
      char_is_int = atoi(argv[i]);
      numbers[level_count] = char_is_int;
      level_count = level_count + 1;
      tot_num = tot_num + char_is_int;
    }
  }

  // initialize arrays for pagetable
  int bitmask_arr[level_count];
  int shift_arr[level_count];
  int entry_count[level_count];

  // assign numbers from input to pagetable arrays
  for(int i = 0; i < level_count; i++) {
    bitmask_arr[i] = numbers[i];
    shift_arr[i] = numbers[i];
    entry_count[i] = numbers[i];
  }

  CalculatePagetableContents(level_count, bitmask_arr, shift_arr, entry_count);

  pagetable *pt = construct_pt(
    level_count,
    bitmask_arr,
    shift_arr,
    entry_count,
    0
  );
  contruct_lvl_zero(pt);
  level *lvl = pt->root_level_ptr;

  /* attempt to open trace file */
  if ((trace_fp = fopen(argv[1],"rb")) == NULL) {
    fprintf(stderr,"cannot open %s for reading\n",argv[1]);
    return 1.;
  }

  while(!feof(trace_fp)) {

    if((i >= N && N != 0) || (level_count == 0) || (tot_num > 32)) break;

    // get next address to be read
    if(NextAddress(trace_fp, &trace)) {
      logical_addr = AddressDecoder(&trace);
      i++;

      m = PageLookup(pt, logical_addr);

      // if the pagelookup is NULL, we have add it to our pagetable
      // this increments a miss
      if(m == NULL) {
        PageInsertLevel(lvl, logical_addr, frame);
        offset = FindOffset(pt, logical_addr);

        phys_addr = FindPhysicalAddress(pt, logical_addr, offset, tot_num);
        frame = frame + 1;
        miss = miss + 1;

        if(p == TRUE) {
          PrintPageToFrame(pt, m, logical_addr, tot_num, out);
        }
      }
      // else the page entry is ni the table so it's a hit
      else {
        offset = FindOffset(pt, logical_addr);
        phys_addr = FindPhysicalAddress(pt, logical_addr, offset, tot_num);
        hit = hit + 1;
      }

      if(t == TRUE) {
        PrintLogicalToPhysical(logical_addr, phys_addr);
      }
    }
  }
  
  float hit_perc;
  float miss_perc;

  if(isN == FALSE) {
    hit_perc = ((float)hit / (float)i) * (float)100;
    miss_perc = ((float)miss / (float)i) * (float)100;
  }
  else {
    hit_perc = ((float)hit / (float)N) * (float)100;
    miss_perc = ((float)miss / (float)N) * (float)100;
  }

  for(int i = 0; i < 32 - tot_num; i++) {
    page_size = 2 * page_size;
  }

  printf("Page size: %u\n", page_size);
  printf("Hits %d (%.2f%c), ", hit, hit_perc, 37);
  printf("Misses %d (%.2f%c) ", miss, miss_perc, 37);
  printf("# Addresses %lu\n", i);

  printf("Bytes used: %d\n", pt->table_size);

  FreePagetable(pt);
  //free(pt);
} 
