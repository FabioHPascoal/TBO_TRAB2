#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node {
    int keyAmt;
    bool isLeaf;
    int nodePos;
    void **keys;
    void **values;
    Node **childNodes;
};

Node *node_create(int t, bool isLeaf, int nodePos) {
    Node *node = malloc(sizeof(Node));

    node->keyAmt = 0;
    node->isLeaf = isLeaf;
    node->nodePos = nodePos;
    node->keys = malloc(sizeof(void *) * (t - 1));
    node->values = malloc(sizeof(void *) * (t - 1));
    node->childNodes = malloc(sizeof(Node *) * (t));

    return node;
}

void node_destroy(Node *node, void (*key_destructor)(void *), void (*value_destructor)(void *)) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->keyAmt; i++) {
        if (key_destructor != NULL) {
            key_destructor(node->keys[i]);
        }
        if (value_destructor != NULL) {
            value_destructor(node->values[i]);
        }
    }

    for (int i = 0; i < node->keyAmt + 1; i++) {
        node_destroy(node->childNodes[i], key_destructor, value_destructor);
    }

    free(node->keys);
    free(node->values);
    free(node->childNodes);
    free(node);
}