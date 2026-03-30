// filename *************************heap.c ************************
// starter

#include <stdint.h>
#include "../RTOS_Labs_common/heap.h"

long StartCritical(void);
void EndCritical(long);
#define  OSCRITICAL_ENTER() { sr = StartCritical(); }
#define  OSCRITICAL_EXIT()  { EndCritical(sr); }


#define HEAP_OK 0
#define HEAP_ERROR_POINTER_OUT_OF_RANGE 1
#define HEAP_ERROR_CORRUPTED_HEAP 2

#define HEAPSIZE 4096

heap_stats_t HeapStats;
uint8_t heap[HEAPSIZE];


//******** Heap_Init *************** 
// Initialize the Heap
// input: none
// output: always HEAP_OK
// notes: Initializes/resets the heap to a clean state where no memory
//  is allocated.
int32_t Heap_Init(void){
  for (int i = 0; i < HEAPSIZE; i++) {
    heap[i] = 0;
  }

  int32_t *p = (int32_t *)heap;

  // set the dummy tags
  p[0] = 0; // top dummy tag
  p[(HEAPSIZE / 4) - 1] = 0; // bottom dummy tag

  // set the initial free block
  int32_t initial_free_size = HEAPSIZE - 8;
  p[1] = initial_free_size;
  p[(HEAPSIZE / 4) - 2] = initial_free_size;

  HeapStats.size = HEAPSIZE;
  HeapStats.free = initial_free_size;
  HeapStats.used = 0;

  
  return HEAP_OK;
}


//******** Heap_Malloc *************** 
// Allocate memory, data not initialized
// input: 
//   desiredBytes: desired number of bytes to allocate
// output: void* pointing to the allocated memory or will return NULL
//   if there isn't sufficient space to satisfy allocation request
void* Heap_Malloc(int32_t desiredBytes){ int sr;

  if (desiredBytes <= 0) return 0;

  OSCRITICAL_ENTER();

  // calculate the required size
  int32_t actual_payload = (desiredBytes + 3) & ~0x03;  // round up the payload
  int32_t size_needed = actual_payload + 8;             // adds on the top and bottom tags

  // start scanning at the first actual block
  int32_t *p = (int32_t *)&heap[4];   // skip the dummy 0

  // first fit search
  while (*p != 0) {     // keep going until we hit the dummy tag (0) at the end

    if (*p >= size_needed) {  // block found
      int32_t old_size = *p;

      // can be split if the leftover block can hold at least an 8 byte block
      if ((old_size - size_needed) >= 8) {
        int32_t new_free_size = old_size - size_needed;

        // setup tags for newly allocated block
        p[0] = -size_needed;
        p[size_needed / 4 - 1] = -size_needed;

        // setup the tags for the remaining free block
        p[size_needed / 4] = new_free_size;
        p[old_size / 4 - 1] = new_free_size;

      } else {
      size_needed = old_size;
      p[0] = -size_needed;
      p[size_needed / 4 - 1] = -size_needed;
      }

      // update the stats
      HeapStats.used += size_needed;
      HeapStats.free -= size_needed;
      
      

      OSCRITICAL_EXIT();

      // return pointer to the payload (one word after the top tag)
      return (void *)&p[1];
    }

    // get absolute value of current tag
    int32_t block_size = (*p < 0) ? -(*p) : (*p);

    // advance the pointer by that many words
    p = p + (block_size / 4);

  }

  // if we get here, the heap is full
  OSCRITICAL_EXIT();
  return 0;
}


//******** Heap_Calloc *************** 
// Allocate memory, data are initialized to 0
// input:
//   desiredBytes: desired number of bytes to allocate
// output: void* pointing to the allocated memory block or will return NULL
//   if there isn't sufficient space to satisfy allocation request
//notes: the allocated memory block will be zeroed out
void* Heap_Calloc(int32_t desiredBytes){  
  void* ptr = Heap_Malloc(desiredBytes);

  if (ptr != 0) {
    // get the top tag
    int32_t *top_tag = (int32_t *)ptr - 1;

    // get the block size
    int32_t block_size = -(*top_tag);

    // get number of words
    int32_t payload_words = (block_size - 8) / 4;

    // treat payload as an array of 32-bit integers
    int32_t *payload = (int32_t *)ptr;

    // zero out the memory
    for (int i = 0; i < payload_words; i++) {
      payload[i] = 0;
    }
  }

  return ptr;

}


//******** Heap_Realloc *************** 
// Reallocate buffer to a new size
//input: 
//  oldBlock: pointer to a block
//  desiredBytes: a desired number of bytes for a new block
//    where the contents of the old block will be copied to
// output: void* pointing to the new block or will return NULL
//   if there is any reason the reallocation can't be completed
// notes: the given block will be unallocated after its contents
//   are copied to the new block
void* Heap_Realloc(void* oldBlock, int32_t desiredBytes){

  // if pointer null, behave like malloc
  if (oldBlock == 0) {
    return Heap_Malloc(desiredBytes);
  }

  // if size is 0, behave like free
  if (desiredBytes <= 0) {
    Heap_Free(oldBlock);
    return 0;
  }

  // allocate a brand new block of the requested size
  void *new_ptr = Heap_Malloc(desiredBytes);
  // return null if heap is full (old block remains valid)
  if (new_ptr == 0) {
    return 0;
  }

  // find out how big the old block was
  int32_t *old_top_tag = (int32_t *)oldBlock - 1;
  int32_t old_block_size = -(*old_top_tag);
  int32_t old_payload_bytes = old_block_size - 8;

  // figure out how much data to copy
  //(we copy whichever is smaller: the old payload size or the new requested size)
  int32_t bytes_to_copy = (old_payload_bytes < desiredBytes) ? old_payload_bytes : desiredBytes;

  // round up to nearest 4-byte word
  int32_t words_to_copy = (bytes_to_copy + 3) / 4;

  // copy the data from the old block to the new block
  int32_t *src = (int32_t *)oldBlock;
  int32_t *dst = (int32_t *)new_ptr;

  for (int i = 0; i < words_to_copy; i++) {
    dst[i] = src[i];
  }

  // free old memory block
  Heap_Free(oldBlock);

  // return pointer to new block
  return new_ptr;

}



// MAYBE DO AN ALIGNMENT CHECK IN HERE??????
//******** Heap_Free *************** 
// return a block to the heap
// input: pointer to memory to unallocate
// output: HEAP_OK if everything is ok;
//  HEAP_ERROR_POINTER_OUT_OF_RANGE if pointer points outside the heap;
//  HEAP_ERROR_CORRUPTED_HEAP if heap has been corrupted or trying to
//  unallocate memory that has already been unallocated;
int32_t Heap_Free(void* pointer){ int sr;
  if (pointer == 0) return HEAP_OK;

  uint32_t addr = (uint32_t)pointer;
  uint32_t heap_start = (uint32_t)&heap[0];
  uint32_t heap_end = (uint32_t)&heap[HEAPSIZE];

  // check bounds (including the dummy tags at beginning and end)
  if (addr <= heap_start || addr >= heap_end) {
    return HEAP_ERROR_POINTER_OUT_OF_RANGE;
  }


  OSCRITICAL_ENTER();

  // find the top tag
  int32_t *top_tag = (int32_t *)pointer - 1;

  // read the size and validate
  int32_t size = -(*top_tag);

  if (size <= 0) {
    OSCRITICAL_EXIT();
    return HEAP_ERROR_CORRUPTED_HEAP;
  }

  // temporarily mark this block as free
  *top_tag = size;
  *(top_tag + (size / 4) - 1) = size;

  // update stats
  HeapStats.used -= size;
  HeapStats.free += size;

  // merge with next block in memory
  int32_t *next_top = top_tag + (size / 4);
  if (*next_top > 0) {
    int32_t next_size = *next_top;
    size = size + next_size; // new size

    // update tags
    *top_tag = size;
    *(top_tag + (size / 4) - 1) = size;
  }

  // merge with previous block in memory
  int32_t *prev_bottom = top_tag - 1;
  if (*prev_bottom > 0) {
    int32_t prev_size = *prev_bottom;
    size = size + prev_size;  // new size

    // move out top tag pointer to the start of the previous block
    top_tag = top_tag - (prev_size / 4);

    // update tags
    *top_tag = size;
    *(top_tag + (size / 4) - 1) = size;
  }

  OSCRITICAL_EXIT();
  return HEAP_OK;
}


//******** Heap_Test *************** 
// Test the heap
// input: none
// output: validity of the heap - either HEAP_OK or HEAP_ERROR_HEAP_CORRUPTED
int32_t Heap_Test(void){
  int32_t *p = (int32_t *)&heap[4]; // Start at the first real block (skip top dummy)
  uint32_t calculated_used = 0;
  uint32_t calculated_free = 0;
  
  // 1. Check Top Dummy Tag
  int32_t *top_dummy = (int32_t *)&heap[0];
  if (*top_dummy != 0) return HEAP_ERROR_CORRUPTED_HEAP;

  // 2. Crawl the heap block by block
  while (*p != 0) {
    int32_t top_tag = *p;
    int32_t block_size = (top_tag < 0) ? -top_tag : top_tag;

    // Rule A: Block size must be a multiple of 4 and at least 8 bytes
    if (block_size < 8 || (block_size % 4) != 0) {
      return HEAP_ERROR_CORRUPTED_HEAP; 
    }

    // Find the bottom tag for this block
    int32_t *bottom_tag_ptr = p + (block_size / 4) - 1;
    
    // Check bounds: Did the math push us past the end of the heap array?
    if ((uint32_t)bottom_tag_ptr >= (uint32_t)&heap[HEAPSIZE]) {
      return HEAP_ERROR_CORRUPTED_HEAP;
    }

    // Rule B: Top Tag MUST exactly equal Bottom Tag
    if (top_tag != *bottom_tag_ptr) {
      return HEAP_ERROR_CORRUPTED_HEAP;
    }

    // Accumulate totals to check against HeapStats later
    if (top_tag > 0) {
      calculated_free += block_size;
    } else {
      calculated_used += block_size;
    }

    // Jump to the next block's Top Tag
    p = p + (block_size / 4);
  }

  // 3. We hit a 0. Verify it is exactly the Bottom Dummy Tag
  int32_t *bottom_dummy = (int32_t *)&heap[HEAPSIZE - 4];
  if (p != bottom_dummy) return HEAP_ERROR_CORRUPTED_HEAP;

  // 4. Verify the global stats match reality
  if (calculated_free != HeapStats.free || calculated_used != HeapStats.used) {
    return HEAP_ERROR_CORRUPTED_HEAP;
  }

  return HEAP_OK; // The heap is perfectly intact!
}


//******** Heap_Stats *************** 
// return the current status of the heap
// input: none
// output: a heap_stats_t that describes the current usage of the heap
int32_t Heap_Stats(heap_stats_t *stats){

  int32_t *p = (int32_t *)&heap[4]; // Start at first real block
  uint32_t available_payload = 0;
  uint32_t used_payload = 0;

  // Crawl the heap to calculate the exact Usable Payload sizes
  while (*p != 0) {
    int32_t tag = *p;
    int32_t block_size = (tag < 0) ? -tag : tag;

    if (tag > 0) {
      // For a free block, the usable space is the physical size minus 8 bytes of tags
      available_payload += (block_size - 8);
    } else {
      // For an allocated block, the user's payload is also the physical size minus tags
      used_payload += (block_size - 8);
    }
    
    p = p + (block_size / 4);
  }

  stats->size = HEAPSIZE;
  stats->free = available_payload;
  stats->used = used_payload;
  
  return HEAP_OK;



/*
  stats->size = HeapStats.size;
  stats->free = HeapStats.free;
  stats->used = HeapStats.used;
  
  return HEAP_OK;
  */
}



