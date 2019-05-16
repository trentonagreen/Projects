#define TRUE 1
#define FALSE -1

// pagetable struct
typedef struct pagetable {
    struct level *root_level_ptr;    
    int *bitmask_arr;
    int *shift_arr;
    int *entry_count;
    int level_count;
    int table_size;
} pagetable;

// level struct
typedef struct level {
  struct pagetable *pagetable_ptr;
  struct level *next_level_arr;
  struct level *next_level_ptr;
  struct map *map_arr;
  int depth;
} level;

// map struct
typedef struct map {
  unsigned int frame;
  int isValid;
} map;

// Contruct pagetable 
struct pagetable* construct_pt(
    int level_count, 
    int bitmask_arr[],
    int shift_arr[], 
    int entry_count[],
    int table_size
);

// Construct level 0
void contruct_lvl_zero(pagetable *pt);

// Insert a level into the pagetable
void PageInsertLevel(struct level *lvl, 
                     unsigned int logical_addr,   
                     unsigned int frame);

// Called by PageInsertLevel if on a leaflevel to create map
void LeafLevel(level *lvl, unsigned int logical_addr, int frame);

// Given a logical address create page by applying masks ans shifting
unsigned int LogicalToPage(unsigned int logical_address,
                           unsigned int mask,
                           unsigned int shift);

// Look into pagetable in page entry isValid or if map exists
struct map* PageLookup(struct pagetable *pt, unsigned int logical_address);

// Calls the next three functions
void CalculatePagetableContents(int level_count, 
                                int bitmask_arr[], 
                                int shift_arr[],  
                                int entry_count[]);

// Given bits from input Calculates the entry count for next level array
void CalculateEntry(int* entry_count, int level_count);

// Given bits from input Calculates shift 
void CalculateShift(int* shift_arr, int level_count);

// Given bits from input Calculates mask
void CalculateMask(int* bitmask_arr, int level_count);

// Prints the page entry and the associated frame
void PrintPageToFrame(struct pagetable *pt, 
                      struct map* m, 
                      unsigned int logical_addr, 
                      int total_numbers, 
                      FILE *out);

// Prints the logical and corresponding physical address
void PrintLogicalToPhysical(unsigned int logical_addr, unsigned int phys_addr);

// Find the physical address
unsigned int FindPhysicalAddress(pagetable* pt, 
                                 unsigned int logical_addr, 
                                 unsigned int offset, 
                                 unsigned int total_number);

// Finds the offset for the logical address
unsigned int FindOffset(struct pagetable *pt, unsigned int logical_addr);

// Counts the number of 1's in a number
unsigned int Count1Bits(unsigned int n);

// Checks if char string is a number
int isNumber(char number[]);

// Frees the contents of the pagetable
void FreePagetable(struct pagetable* pt);