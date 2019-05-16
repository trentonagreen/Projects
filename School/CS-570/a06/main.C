
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdint.h>

#include "DirEntry.h"
#include "BlockDevice.h"
#include "SuperBlock.h"
#include "hexdump.h"
#include "linkedlist.h"
#include "vfs.h"

// should be 1000
#define DEFAULT_BLOCKS 10

void MyBadDebugger() {
  printf("got here\n");
}

void printTable(struct list *fat, uint32_t *freemap) {

  node *tmp = fat->head;

  for(int i = 0; i < DEFAULT_BLOCKS; i++) {
    printf("\tblock:\t%d\t", tmp->block);

    if(tmp->entry != NULL) {
      printf("\tfile:\t%s\t", tmp->entry->fname);
    }
    else if(tmp->freemap != NULL) {
      printf("\tfile:\tFREEMAP\t");
    }
    else if(tmp->superblock != NULL) {
      printf("\tfile:\tSUPERBLOCK");
    } 
    else {
      printf("\tfile:\tNULL\t");
    }

    printf("\tfreebit:\t%d\n", freemap[i]);

    tmp = tmp->next;
  }
}

//void format(BlockDevice *device) {
void format(BlockDevice *device, FileSystem *fs) {
  BlockDevice::result result;

  // create linked list FAT
  printf("\n---------- creating FAT ----------\n");

  //list *fat;
  fs->fat = Construct_List();

  for(int i = 0; i < device->getBlocks(); i++) {
    enqueue(fs->fat, NULL);
  }

  printlist(fs->fat);

  // create bit map based on linked list
  printf("\n---------- creating freemap ----------\n");

  //uint32_t freemap[device->getBlocks()];

  for(int i = 0; i < device->getBlocks(); i++) {
    fs->freemap[i] = 0;
  }

  printTable(fs->fat, fs->freemap);
  
  //create root
  printf("\n---------- creating root ----------\n");
  DirEntry *root = (DirEntry*)malloc(sizeof(DirEntry));
  //root->start_blk = fat->head->block;
  root->size = device->getBlockSize() * 1;  // block size * number of blocks used
  root->directory = true;
  strcpy(root->fname, "/");

  node *tmp = fs->fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if(tmp->block == i && fs->freemap[i] == 0) {
      printf("first free block is %d\n", tmp->block);
      
      tmp->entry = root;

      fs->freemap[i] = 1;
      tmp->freebit = 1;
      root->start_blk = tmp->block;

      result = device->writeBlock(tmp->block, tmp->entry);
      printf("writeBlock %d result %s\n", tmp->block, device->resultMessage(result));
      
      break;
    }
    tmp = tmp->next;
  }

  printTable(fs->fat, fs->freemap);

  // create superblock
  printf("\n---------- creating superblock ----------\n");
  //SuperBlock *superblock = (SuperBlock*)malloc(sizeof(SuperBlock));
  fs->superblock = (SuperBlock*)malloc(sizeof(SuperBlock));
  strcpy(fs->superblock->magic, "TinyFS");
  fs->superblock->fat_block = fs->fat->head->block;

  tmp = fs->fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if( strcmp(tmp->entry->fname, "/") == 0) {
      fs->superblock->fat_idx_root = tmp->block;
      printf("root is in block %d\n", tmp->block);
      break;
    }
    tmp = tmp->next;
  }

  tmp = fs->fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if(tmp->freemap != NULL) {
        fs->superblock->free_block = tmp->block;
        printf("freemap is in block %d\n", tmp->block);
        break;
    }
    tmp = tmp->next;
  }
  
  tmp = fs->fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if(tmp->block == i && fs->freemap[i] == 0) { 
      printf("first free block is %d\n", tmp->block);

      tmp->superblock = fs->superblock;

      fs->freemap[i] = 1;
      tmp->freebit = 1;

      result = device->writeBlock(tmp->block, tmp);
      printf("writeBlock %d result %s\n", tmp->block, device->resultMessage(result));
      
      break;
    }
    tmp = tmp->next;
  }

  printTable(fs->fat, fs->freemap);

  // place freemap in fat
  printf("\n---------- placing free map in fat ----------\n");

  tmp = fs->fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if(tmp->block == i && fs->freemap[i] == 0) {
      printf("first free block is %d\n", tmp->block);

      fs->freemap[i] = 1;
      tmp->freebit = 1;
      tmp->freemap = fs->freemap;

      //result = device->writeBlock(tmp->block, tmp);
      //printf("writeBlock %d result %s\n", tmp->block, device->resultMessage(result));

      break;
    }
    tmp = tmp->next;
  }

  printTable(fs->fat, fs->freemap);

  /*
  // create bs blocks
  printf("\n---------- creating bs block ----------\n");

  DirEntry *newdir = (DirEntry*)malloc(sizeof(DirEntry));
  newdir->directory = false;
  newdir->size = device->getBlockSize() * 1;
  strcpy(newdir->fname, "newdir");

  tmp = fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if(tmp->block == i && freemap[i] == 0) {
      printf("first free block is %d\n", tmp->block);
      newdir->start_blk = tmp->block;

      tmp->entry = newdir;

      freemap[i] = 1;
      tmp->freebit = 1;

      result = device->writeBlock(tmp->block, tmp->entry);
      printf("writeBlock %d result %s\n", tmp->block, device->resultMessage(result));
      break;
    }
    tmp = tmp->next;
  }

  printTable(fat, freemap);
  */

}

void place(BlockDevice *device, struct FileSystem *fs) {
  printf("\n---------- placing new file onto disk ----------\n");
  BlockDevice::result result;

  // placed in root directory
  DirEntry *newfile = (DirEntry*)malloc(sizeof(DirEntry));
  newfile->directory = false;
  newfile->size = device->getBlockSize() * 1;
  strcpy(newfile->fname, ".txt");

  node *tmp = fs->fat->head;
  for(int i = 0; i < device->getBlocks(); i++) {
    if(tmp->block == i && fs->freemap[i] == 0) {
      printf("first free block is %d\n", tmp->block);
      newfile->start_blk = tmp->block;

      tmp->entry = newfile;

      fs->freemap[i] = 1;
      tmp->freebit = 1;

      result = device->writeBlock(tmp->block, tmp->entry);
      printf("writeBlock %d result %s\n", tmp->block, device->resultMessage(result));
      break;
    }
    tmp = tmp->next;
  }

  printTable(fs->fat, fs->freemap);
}

int main (int argc, char **argv) {
  printf("this is ass6 and i want to kill myself\n");

  printf("\n---------- checking virtual disk ----------\n");

  const char *disk = "foobar.dsk";
  BlockDevice *device;
  
  uint32_t freemap[DEFAULT_BLOCKS];

  FileSystem *fs = (FileSystem*)malloc(sizeof(FileSystem));
  fs->fat = NULL;
  fs->superblock = NULL;
  fs->freemap = freemap;

  struct stat statbuf;
  if (stat(disk, &statbuf) == -1) {
    device = new BlockDevice(disk, DEFAULT_BLOCKS);
    printf("\tcreated disk : %s\n", disk);

    printf("\n---------- formatting disk ----------\n");
    format(device, fs);
  } 
  else {
    device = new BlockDevice(disk);
    printf("\t* disk already exists\n");
  }
  //printf("\t* number of blocks on device: %d\n", device->getBlocks());
  
  //printf("\n---------- formatting disk ----------\n");
  //format(device);

  place(device, fs);

  
  int bits[DEFAULT_BLOCKS] = {0,1,2,3,4,5,6,7,8,9};
  int *nextFree = bits;
  
  //lastUsed = lastUsed + 1;
  //printf("lastUsed: %d\n", lastUsed[0]);
  
  
  for(int i = 0; i < 5; i++) {
    bits[i] = 1;

    nextFree++;
  }

  for(int i = 0; i < 10; i++) {
    printf("bits: %d\n", bits[i]);
    //printf("lastUsed: %d\n", nextFree[i]);
  }
  printf("nextFree: %d\n\n", nextFree[0]);
  
  /*
 *  handle args, TODO move up 
 */

  // argv[1] = disk
  // argv[2] = text file with commands
  // argv[3] (optional) = number of blocks in disk

  if(argc < 3) {
    printf("NOT ENOUGH ARGS\n");
    return 0; 
  }

  char *diskName = argv[1];
  char *txt = argv[2];
  char *nBlocks = argv[3] ;

  printf("disk:\t%s\n", diskName);
  printf("text:\t%s\n",txt);
  printf("block:\t%s\n\n", nBlocks);

  FILE *fptr;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *token;

  fptr = fopen(txt, "r");
  
  if (fptr == NULL) {
    printf("Cannot open file %s\n", txt);
  }

  while ((read = getline(&line, &len, fptr)) != -1) {
    //printf("line: %s\n", line);

    token = strtok(line, " \n");
    printf("token*:\t%s\n", token);
    // add to command string list
     
    if(strcmp(token, "format") == 0) {
      printf("token is %s\n", token);
    }

    while (token != NULL) {
      token = strtok(NULL, " \n");
      
      if(token == NULL)
        break;

      // add to command string list
      printf("token:\t%s\n", token);
    }
    printf("\n"); 
  }

  long int fileSize = 0;
  fseek(fptr, 0, SEEK_END);
  fileSize = ftell(fptr);
  if(fileSize != -1) {
    printf("File size in bytes:\t%ld\n", fileSize);
  }
  else {
    printf("Error finding file size\n");
  }

}
