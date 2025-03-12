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

void bt_split_child(int t, int i, Node *nonFullNode, Node *fullNode) {
    // Node *newNode = node_create(t, is_node_leaf(fullNode), node_get_pos(fullNode) +1);
    // node_set_key_amt(newNode, t/2);

    // // Copying second half of fullNode's contents to the new node
    // for (int j = 0; j < t -1; j++) {
    //     void *key = node_get_key(fullNode, j + t);
    //     void *val = node_get_val(fullNode, j + t);

    //     node_set_key_val(newNode, key, val, j);
    // }

    // // Copying second half of fullNode's children to the new node, if it has any
    // if (!is_node_leaf(fullNode)) {
    //     for (int j = 0; j < t; j++) {
    //         Node *childNode = node_get_child(fullNode, j + t);
    //         node_set_child(newNode, childNode, j);
    //     }
    // }

    // // Updating the number of keys on the left node
    // node_set_key_amt(fullNode, t -(t/2) -1);

    // for (int j = node_get_key_amt(nonFullNode); j > i; j--) {

    // }


    // void *key = node_get_key(fullNode, )
    // node_set_key_val(nonFullNode,  );
    
    // // Increase amount of keys in nonFullNode by 1
    // node_set_key_amt(nonFullNode, node_get_key_amt(nonFullNode) + 1);
}

void bt_insert_nonfull() {

}

void bt_insert(BT *bt, int key, int val) {

    // Node *node = bt->root;

    // // Root node is full
    // if (node_get_key_amt(node) == bt->t -1) {
    //     Node *newNode = node_create(bt->t, false, 0);
    //     bt->root = newNode;
    //     node_set_nodePos(node, 1);
    //     node_set_child(newNode, node, 0);
    //     bt_split_child(bt->t, 0, newNode, node);
    //     bt_insert_nonfull(newNode, key, val);
    // }
    
    // // Root node is not full
    // else {
    //     bt_insert_nonfull(node, key, val);
    // }
}

NodeIdxTuple *bt_search(BT *bt, int key) {
    return node_search(bt->binFile, bt->t, 0, key);
}

void bt_print(BT *bt) {
    if (!bt || !bt->root) return;

    FILE *file = fopen(FILENAME, BINARY_READ);
    if (!file) return;
    
    Deque *queue = deque_construct();
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
