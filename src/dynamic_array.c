#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new dynamic array with the specified initial capacity
DynamicArray* createDynamicArray(size_t initialCapacity) {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (array == NULL) {
        perror("Failed to create dynamic array");
        exit(EXIT_FAILURE);
    }
    array->data = (void**)malloc(initialCapacity * sizeof(void*));
    if (array->data == NULL) {
        perror("Failed to allocate array data");
        free(array);
        exit(EXIT_FAILURE);
    }
    array->size = 0;
    array->capacity = initialCapacity;
    return array;
}

// Get an element from the array by index
void* getElement(DynamicArray* array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        return NULL;
    }
    return array->data[index];
}

// Set an element in the array at the specified index
void setElement(DynamicArray* array, size_t index, void* element) {
    if (index >= array->capacity) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    array->data[index] = element;
    if (index >= array->size) {
        array->size = index + 1;
    }
}

// Append an element to the end of the array
void appendElement(DynamicArray* array, void* element) {
    if (array->size >= array->capacity) {
        // Resize the array if needed
        resizeDynamicArray(array, array->capacity * 2);
    }
    array->data[array->size++] = element;
}

// Resize the dynamic array to a new capacity
void resizeDynamicArray(DynamicArray* array, size_t newCapacity) {
    void** newData = (void**)realloc(array->data, newCapacity * sizeof(void*));
    if (newData == NULL) {
        perror("Failed to resize dynamic array");
        exit(EXIT_FAILURE);
    }
    array->data = newData;
    array->capacity = newCapacity;
}

// Free the memory used by the dynamic array
void freeDynamicArray(DynamicArray* array) {
    if (array == NULL) return;
    free(array->data);
    free(array);
}
