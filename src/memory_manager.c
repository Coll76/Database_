#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize the memory manager
MemoryManager* initMemoryManager(size_t size) {
    MemoryManager* manager = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (manager == NULL) {
        perror("Failed to initialize memory manager");
        exit(EXIT_FAILURE);
    }
    
    // Allocate a large block of memory
    void* initialMemory = malloc(size);
    if (initialMemory == NULL) {
        perror("Failed to allocate initial memory");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the free list with a single large block
    manager->freeList = (FreeBlock*)initialMemory;
    manager->freeList->size = size;
    manager->freeList->next = NULL;
    
    return manager;
}

// Allocate memory from the manager
void* allocate(MemoryManager* manager, size_t size) {
    FreeBlock* prev = NULL;
    FreeBlock* current = manager->freeList;
    
    // Find a suitable block
    while (current != NULL) {
        if (current->size >= size) {
            // Found a block large enough
            if (current->size > size + sizeof(FreeBlock)) {
                // Split the block
                FreeBlock* newBlock = (FreeBlock*)((char*)current + sizeof(FreeBlock) + size);
                newBlock->size = current->size - size - sizeof(FreeBlock);
                newBlock->next = current->next;
                
                current->size = size;
                current->next = newBlock;
            }
            
            // Remove the block from the free list
            if (prev == NULL) {
                manager->freeList = current->next;
            } else {
                prev->next = current->next;
            }
            
            return (char*)current + sizeof(FreeBlock);
        }
        
        prev = current;
        current = current->next;
    }
    
    // No suitable block found
    return NULL;
}

// Deallocate memory and add it back to the manager
void deallocate(MemoryManager* manager, void* ptr) {
    if (ptr == NULL) return;
    
    FreeBlock* block = (FreeBlock*)((char*)ptr - sizeof(FreeBlock));
    FreeBlock* current = manager->freeList;
    FreeBlock* prev = NULL;
    
    // Insert the block into the free list in sorted order
    while (current != NULL && (char*)current < (char*)block) {
        prev = current;
        current = current->next;
    }
    
    block->next = current;
    
    if (prev == NULL) {
        manager->freeList = block;
    } else {
        prev->next = block;
    }
    
    // Coalesce adjacent free blocks
    if (block->next != NULL && (char*)block + sizeof(FreeBlock) + block->size == (char*)block->next) {
        block->size += sizeof(FreeBlock) + block->next->size;
        block->next = block->next->next;
    }
    
    if (prev != NULL && (char*)prev + sizeof(FreeBlock) + prev->size == (char*)block) {
        prev->size += sizeof(FreeBlock) + block->size;
        prev->next = block->next;
    }
}

// Free the memory manager and all allocated memory
void freeMemoryManager(MemoryManager* manager) {
    if (manager == NULL) return;
    
    FreeBlock* current = manager->freeList;
    while (current != NULL) {
        FreeBlock* next = current->next;
        free(current);
        current = next;
    }
    
    free(manager);
}
