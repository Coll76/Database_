#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

// Define the dynamic array structure
typedef struct DynamicArray {
    void** data;     // Array of pointers to elements
    size_t size;     // Current number of elements
    size_t capacity; // Current capacity of the array
} DynamicArray;

// Function prototypes
DynamicArray* createDynamicArray(size_t initialCapacity);
void* getElement(DynamicArray* array, size_t index);
void setElement(DynamicArray* array, size_t index, void* element);
void appendElement(DynamicArray* array, void* element);
void resizeDynamicArray(DynamicArray* array, size_t newCapacity);
void freeDynamicArray(DynamicArray* array);

#endif // DYNAMIC_ARRAY_H
