#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "BT.h"
#include "deque.h"

#define FILENAME "binary.exe"
#define BINARY_WRITE "wb"
#define BINARY_READ "rb"

struct BT {
    FILE *binFile;
    Node *root;
    int nodeAmt;
    int t;
};

BT *bt_create(int t, int firstKey, int firstVal) {

    // Allocate memory for the BT
    BT *bt = malloc(sizeof(BT));
    if (!bt) return NULL;

    // Create binary file on write mode
    bt->binFile = fopen(FILENAME, BINARY_WRITE);

    if (!bt->binFile) {
        free(bt);
        return NULL;
    }

    // The only node that will be in main memory all the time is the root
    bt->root = node_create(t, true, 0);
    if (!bt->root) {
        fclose(bt->binFile);
        free(bt);
        return NULL;
    }

    // Insert the first key-value pair in the root
    node_insert(bt->root, firstKey, firstVal);

    // Write root node data to the binary file
    disk_write(bt->binFile, bt->root, t);

    bt->nodeAmt = 1;
    bt->t = t;

    return bt;
}

void bt_destroy(BT *bt) {
    fclose(bt->binFile);
    node_destroy(bt->root);
    free(bt);
}

void bt_insert(BT *bt, int key, int val) {
    
    // To update changed nodes in the file
    FILE *readableFile = fopen(FILENAME, BINARY_READ);
    if (!readableFile) return;

    // Stores the position of nodes visited from root to a leaf node
    Deque *nodeStack = deque_construct(20);
    if (!nodeStack) {
        fclose(readableFile);
        return;
    }

    // Will start as the root, and finish as a leaf
    Node *node = NULL;
    int nodeIdx = 0;
    int keyIdx = 0;

    // Iterates from root to leaf node
    while (true) {
        node = disk_read(readableFile, nodeIdx, bt->t);
        keyIdx = single_node_search(node, bt->t, key);

        // Key is already in the tree
        if ((keyIdx < bt->t -1) && (node_get_key(node, keyIdx) == key)) {
            node_set_key_val(node, key, val, keyIdx);
            disk_write(bt->binFile, node, bt->t);
            node_destroy(node);
            fclose(readableFile);
            deque_destroy(nodeStack);
            return;
        }

        if (is_node_leaf(node)) break;

        nodeIdx = node_get_child_pos(node, keyIdx);
        deque_push_front(nodeStack, node_get_pos(node));
        node_destroy(node);
    }

    // Leaf node is not full
    if (node_get_key_amt(node) < bt->t - 1) {
        node_insert(node, key, val);
        disk_write(bt->binFile, node, bt->t);
    }

    // Leaf node is full
    // else node_split(); // To be implemented

    node_destroy(node);
    deque_destroy(nodeStack);
    fclose(readableFile);
}

NodeIdxTuple *bt_search(BT *bt, int key) {
    return node_search(bt->binFile, bt->t, 0, key);
}

void bt_print(BT *bt) {
    if (!bt || !bt->root) return;

    FILE *file = fopen(FILENAME, BINARY_READ);
    if (!file) return;
    
    Deque *queue = deque_construct(50);
    deque_push_back(queue, 0);

    while (deque_get_size(queue) > 0) {
        
        Node *current = disk_read(file, deque_pop_front(queue), bt->t);

        printf("[");
        // Processa os valores do nó atual
        for (int i = 0; i < node_get_key_amt(current); i++) {
            printf("%d, ", node_get_key(current, i));
        }
        printf("]");

        // Enfileira os filhos (se não for folha)
        if (!is_node_leaf(current)) {
            for (int i = 0; i <= node_get_key_amt(current); i++) {
                deque_push_back(queue, node_get_child_pos(current, i));
            }
        }

        node_destroy(current);
    }
    printf("\n");
    
    fclose(file);
    deque_destroy(queue);
}
