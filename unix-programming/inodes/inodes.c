/*
 * inodes.c
 *
 *  Created on: Nov 29, 2013
 *      Author: jcyescas
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DIRECT_POINTERS 123

#define POINTERS_PER_BLOCK 128

#define BLOCK_SECTOR_SIZE 512

/* Yields X divided by STEP, rounded up.
 For X >= 0, STEP >= 1 only. */
#define DIV_ROUND_UP(X, STEP) (((X) + (STEP) - 1) / (STEP))

/* There are 123 direct blocks pointers in the inode_disk pointing to blocks of 512 bytes*/
#define DIRECT_BLOCKS_SIZE 123 * 512

/* There is 1 indirect block in the inode_disk pointing to a block of 128 direct blocks pointers. */
#define INDIRECT_BLOCKS_SIZE POINTERS_PER_BLOCK * 512

/* There is 1 double indirect block in the inode_disk pointing to a block of 128 indirect blocks pointers. */
#define DOULBE_INDIRECT_BLOCKS_SIZE POINTERS_PER_BLOCK * POINTERS_PER_BLOCK * 512

/* On-disk inode.
 Must be exactly BLOCK_SECTOR_SIZE bytes long. */
struct inode_disk
{
  uint32_t type; /* Inode type (file or directory)*/
  uint32_t length; /* File size in bytes. */
  uint32_t magic; /* Magic number. */
  uint32_t direct_blocks[123]; /* Points to blocks of data (62,976 bytes). */
  uint32_t indirect_block; /* Points to block of pointers that points to blocks of data (65,536 bytes). */
  uint32_t double_indirect_block; /* Points to block of pointers that point to block of pointers to blocks of data (8,388,608 bytes).*/
};

/* In-memory inode. */
struct inode
{
  uint32_t sector; /* Sector number of disk location. */
  int open_cnt; /* Number of openers. */
  int deny_write_cnt; /* 0: writes ok, >0: deny writes. */
  struct inode_disk data; /* Inode content. */
  uint32_t indirect_blocks[POINTERS_PER_BLOCK];
  uint32_t double_indirect_block[POINTERS_PER_BLOCK][POINTERS_PER_BLOCK];
};

void
initialize_array(uint32_t array[], int size, int start)
{
  int i;
  for (i = 0; i < size; i++)
    {
      array[i] = start;
      start++;
    }

}

void
print_blocks(struct inode *inode)
{
  printf("Direct blocks\n");
  int i;
  for (i = 0; i < 123; i++)
    printf("%u ", inode->data.direct_blocks[i]);

  printf("\nIndirect blocks\n");
  for (i = 0; i < 128; i++)
    printf("%u ", inode->indirect_blocks[i]);

  printf("\nDouble indirect blocks\n");

  for (i = 0; i < 128; i++)
    printf("%u ", inode->double_indirect_block[0][i]);

  printf("\n");
  for (i = 0; i < 128; i++)
    printf("%u ", inode->double_indirect_block[1][i]);

  printf("\n");
  for (i = 0; i < 128; i++)
    printf("%u ", inode->double_indirect_block[127][i]);
}

/* Returns the block device sector that contains byte offset POS
 within INODE.
 Returns -1 if INODE does not contain data for a byte at offset
 POS.
 */
uint32_t
byte_to_sector(const struct inode *inode, uint32_t pos)
{
  if (pos <= inode->data.length)
    {
      if (pos <= DIRECT_BLOCKS_SIZE)
        {
          /* Return the first block if the position is zero. */
          if (pos == 0)
            return inode->data.direct_blocks[0];

          /* Direct blocks. */
          uint32_t sector_index = DIV_ROUND_UP (pos, BLOCK_SECTOR_SIZE) - 1;
          return inode->data.direct_blocks[sector_index];
        }
      else if (pos <= (INDIRECT_BLOCKS_SIZE + DIRECT_BLOCKS_SIZE))
        {
          /* Indirect blocks */
          uint32_t relative_pos = pos - DIRECT_BLOCKS_SIZE;
          uint32_t sector_index = DIV_ROUND_UP (relative_pos, BLOCK_SECTOR_SIZE)
              - 1;
          return (uint32_t) inode->indirect_blocks[sector_index];
        }
      else
        {
          /* Double indirect blocks  */
          uint32_t relative_pos = pos - (INDIRECT_BLOCKS_SIZE + DIRECT_BLOCKS_SIZE);

          int index;
          int range = INDIRECT_BLOCKS_SIZE;
          for (index = 0; index < POINTERS_PER_BLOCK; index++)
            {
              if (relative_pos <= range)
                {
                  break;
                }
              range += INDIRECT_BLOCKS_SIZE;
            }

          relative_pos -= (INDIRECT_BLOCKS_SIZE * index);
          uint32_t sector_index = DIV_ROUND_UP (relative_pos, BLOCK_SECTOR_SIZE) - 1;
          return inode->double_indirect_block[index][sector_index];
        }
    }
  else
    return -1;
}

void
print_sector_offset(struct inode *inode, uint32_t offset,
    uint32_t expected_sector)
{
  uint32_t sector = byte_to_sector(inode, offset);
  printf("\n\nOffset [%d], Sector [%d]", offset, sector);
  if (sector != expected_sector)
    printf(
        "\nSector is invalid ..............................................");

}

void
test1()
{
  /* It tests that the sector is returned appropriately given the offset. */
  printf("Executing..............\n");

  struct inode_disk inode_disk;
  struct inode inode;
  inode.data = inode_disk;
  inode.data.length = 8517120;

  initialize_array(inode.data.direct_blocks, 123, 101);

  initialize_array(inode.indirect_blocks, 128, 401);

  uint32_t direct_block1[128];
  initialize_array(direct_block1, 128, 1001);

  uint32_t direct_block2[128];
  initialize_array(direct_block2, 128, 2001);

  uint32_t direct_block3[128];
  initialize_array(direct_block3, 128, 6001);

  uint32_t direct_block4[128];
  initialize_array(direct_block4, 128, 7001);

  initialize_array(inode.double_indirect_block[0], 128, 1001);
  initialize_array(inode.double_indirect_block[1], 128, 2001);
  initialize_array(inode.double_indirect_block[60], 128, 6001);
  initialize_array(inode.double_indirect_block[127], 128, 7001);

  print_blocks(&inode);

  print_sector_offset(&inode, 0, 101);

  print_sector_offset(&inode, 1, 101);

  print_sector_offset(&inode, 512, 101);

  print_sector_offset(&inode, 520, 102);

  print_sector_offset(&inode, 62400, 222);

  print_sector_offset(&inode, 62976, 223);

  print_sector_offset(&inode, 62977, 401);

  print_sector_offset(&inode, 128512, 528);

  print_sector_offset(&inode, 128000, 527);

  print_sector_offset(&inode, 128513, 1001);

  print_sector_offset(&inode, 194048, 1128);

  print_sector_offset(&inode, 129536, 1002);

  print_sector_offset(&inode, 194049, 2001);

  print_sector_offset(&inode, 194600, 2002);

  print_sector_offset(&inode, 259584, 2128);

  print_sector_offset(&inode, 4060673, 6001);

  print_sector_offset(&inode, 4060674, 6001);

  print_sector_offset(&inode, 4061373, 6002);

  print_sector_offset(&inode, 4126208, 6128);

  print_sector_offset(&inode, 8451585, 7001);

  print_sector_offset(&inode, 8452300, 7002);

  print_sector_offset(&inode, 8517120, 7128);

  print_sector_offset(&inode, 8517119, 7128);

  print_sector_offset(&inode, 8516608, 7127);

  print_sector_offset(&inode, 8516096, 7126);

  print_sector_offset(&inode, 8515584, 7125);
}

/* Initializes all the elements of the array to zero.
 */
static void
initialize_array_to_zeros(uint32_t array[], uint32_t size)
{
  int i;
  for (i = 0; i < size; i++)
    array[i] = 0;
}

/* It sets the contiguous sector numbers in the direct, indirect and double indirect blocks at the creation
 * of the inode. */
static void
inode_set_contiguous_sectors(struct inode_disk *disk_inode,
    uint32_t indirect_blocks[], uint32_t double_indirect_block[][POINTERS_PER_BLOCK], uint32_t sectors, uint32_t start)
{
  /* Initializing DIRECT blocks. */
  int index;
  for (index = 0; index < sectors && index < DIRECT_POINTERS; index++)
    disk_inode->direct_blocks[index] = start + index;

  start += index;
  sectors -= index;

  /* If there are more sectors per assign, continue assigning the number of sectors to the
   * INDIRECT blocks. */
  if (sectors > 0)
    {
      for (index = 0; index < sectors && index < POINTERS_PER_BLOCK; index++)
        indirect_blocks[index] = start + index;
      start += index;
      sectors -= index;
    }

  /* If there are more sectors per assign, continue assigning the number of sectors to the
   * DOUBLE INDIRECT blocks. */
  if (sectors > 0)
    {
      int i, j, count;
      count = 0;
      for (i = 0; count < sectors && i < POINTERS_PER_BLOCK; i++)
        for (j = 0; count < sectors && j < POINTERS_PER_BLOCK; j++)
          {
            double_indirect_block[i][j] = start + count;
            count++;
          }
    }
}

static bool
inode_create()
{
  struct inode_disk disk_inode;
  uint32_t indirect_blocks[POINTERS_PER_BLOCK];
  uint32_t double_indirect_block[POINTERS_PER_BLOCK][POINTERS_PER_BLOCK];

  /* Setting the values in the array to ZERO. */
  initialize_array_to_zeros(disk_inode.direct_blocks, DIRECT_POINTERS);
  initialize_array_to_zeros(indirect_blocks, POINTERS_PER_BLOCK);

  int j;
  for (j = 0; j < POINTERS_PER_BLOCK; j++)
    initialize_array_to_zeros(double_indirect_block[j], POINTERS_PER_BLOCK);

  /* Setting the values for the sectors.*/
  uint32_t start = 101;
  uint32_t sectors = 128 + 123 + 121;
  inode_set_contiguous_sectors(&disk_inode, indirect_blocks, double_indirect_block, sectors, start);


  printf("\nDIRECT BLOCKS\n");
  int i;
  for (i = 0; i < DIRECT_POINTERS; i++)
    printf("%d ", disk_inode.direct_blocks[i]);


  printf("\n\nINDIRECT BLOCKS\n");
  for (i = 0; i < POINTERS_PER_BLOCK; i++)
    printf("%d ", indirect_blocks[i]);


  printf("\n\nDOUBLE INDIRECT BLOCKS\n");
  for (j = 0; j < POINTERS_PER_BLOCK; j++)
    {
      for (i = 0; i < POINTERS_PER_BLOCK; i++)
        printf("%d ", double_indirect_block[j][i]);
      printf("\n");
    }

  return true;
}




int
main()
{
  inode_create();
  test1();
  //inode_create_set_sectors()
}
