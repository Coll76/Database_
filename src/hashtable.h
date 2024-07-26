#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 100 // Size of the hash table

// Define a node in the hash table
typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next; // Pointer to the next node for collision resolution
} HashNode;

// Define the hash table
typedef struct HashTable {
    HashNode* table[TABLE_SIZE]; // Array of pointers to hash nodes
} HashTable;

// Function prototypes
HashTable* createHashTable();
int hash(int key);
void insertHashTable(HashTable* hashTable, int key, int value);
int searchHashTable(HashTable* hashTable, int key);
void deleteHashTable(HashTable* hashTable, int key);
void freeHashTable(HashTable* hashTable);

#endif // HASHTABLE_H
