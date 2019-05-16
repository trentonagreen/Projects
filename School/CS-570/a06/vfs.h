
typedef struct FileSystem {
  struct list *fat;
  struct SuperBlock *superblock;
  uint32_t *freemap;
} FileSystem;
