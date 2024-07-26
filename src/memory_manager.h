#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

// Define the free memory block structure
typedef struct FreeBlock {
    size_t size;
    struct FreeBlock* next;
} FreeBlock;

// Define the memory manager structure
typedef struct MemoryManager {
    FreeBlock* freeList; // Pointer to the list of free memory blocks
} MemoryManager;

// Function prototypes
MemoryManager* initMemoryManager(size_t size);
void* allocate(MemoryManager* manager, size_t size);
void deallocate(MemoryManager* manager, void* ptr);
void freeMemoryManager(MemoryManager* manager);

#endif // MEMORY_MANAGER_H
