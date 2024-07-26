#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <stdbool.h>

#define MAX_KEYS 4 // Maximum number of keys in a node
#define MIN_KEYS (MAX_KEYS / 2) // Minimum number of keys in a non-root node

// Define B+ Tree Node
typedef struct BPlusTreeNode {
    int keys[MAX_KEYS];
    struct BPlusTreeNode* children[MAX_KEYS + 1];
    int numKeys;
    bool isLeaf;
} BPlusTreeNode;

// Function prototypes
BPlusTreeNode* createNode(bool isLeaf);
void insert(BPlusTreeNode** root, int key);
void splitChild(BPlusTreeNode* parent, int index);
void insertNonFull(BPlusTreeNode* node, int key);
void traverse(BPlusTreeNode* root);

#endif // BPLUSTREE_H
