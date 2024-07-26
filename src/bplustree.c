#include "bplustree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new B+ Tree Node
BPlusTreeNode* createNode(bool isLeaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    memset(node->children, 0, sizeof(node->children)); // Initialize children to NULL
    return node;
}

// Insert a key into the B+ Tree
void insert(BPlusTreeNode** root, int key) {
    BPlusTreeNode* r = *root;
    if (r->numKeys == MAX_KEYS - 1) { // Root is full
        BPlusTreeNode* s = createNode(false); // Create a new root
        *root = s;
        s->children[0] = r;
        splitChild(s, 0);
        insertNonFull(s, key);
    } else {
        insertNonFull(r, key);
    }
}

// Insert a key into a non-full node
void insertNonFull(BPlusTreeNode* node, int key) {
    int i = node->numKeys - 1;
    if (node->isLeaf) { // If the node is a leaf
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else { // If the node is not a leaf
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == MAX_KEYS - 1) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Split the child of a node
void splitChild(BPlusTreeNode* parent, int index) {
    BPlusTreeNode* fullChild = parent->children[index];
    BPlusTreeNode* newChild = createNode(fullChild->isLeaf);
    
    parent->children[index + 1] = newChild;
    parent->keys[index] = fullChild->keys[MIN_KEYS];
    parent->numKeys++;

    newChild->numKeys = MIN_KEYS;
    fullChild->numKeys = MIN_KEYS;

    for (int i = 0; i < MIN_KEYS; i++) {
        newChild->keys[i] = fullChild->keys[i + MIN_KEYS + 1];
    }
    
    if (!fullChild->isLeaf) {
        for (int i = 0; i <= MIN_KEYS; i++) {
            newChild->children[i] = fullChild->children[i + MIN_KEYS + 1];
        }
    }
}

// Traverse the B+ Tree (for debugging)
void traverse(BPlusTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->numKeys; i++) {
            if (!root->isLeaf) {
                traverse(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }
        if (!root->isLeaf) {
            traverse(root->children[root->numKeys]);
        }
    }
}
