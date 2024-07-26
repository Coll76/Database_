#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>

// Create a new hash table
HashTable* createHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        perror("Failed to create hash table");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Insert a key-value pair into the hash table
void insertHashTable(HashTable* hashTable, int key, int value) {
    int index = hash(key);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (newNode == NULL) {
        perror("Failed to insert into hash table");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// Search for a value by key in the hash table
int searchHashTable(HashTable* hashTable, int key) {
    int index = hash(key);
    HashNode* node = hashTable->table[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1; // Key not found
}

// Delete a key-value pair from the hash table
void deleteHashTable(HashTable* hashTable, int key) {
    int index = hash(key);
    HashNode* node = hashTable->table[index];
    HashNode* prev = NULL;
    while (node != NULL) {
        if (node->key == key) {
            if (prev == NULL) {
                hashTable->table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Free the memory used by the hash table
void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = hashTable->table[i];
        while (node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(hashTable);
}
