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
    if (!node) return NULL;

    node->keyAmt = 0;
    node->isLeaf = isLeaf;
    node->nodePos = nodePos;

    node->keys = malloc(sizeof(void *) * (t - 1));
    node->values = malloc(sizeof(void *) * (t - 1));
    node->childNodes = calloc(t, sizeof(Node *));

    if (!node->keys || !node->values || !node->childNodes) {
        free(node->keys);
        free(node->values);
        free(node->childNodes);
        free(node);
        return NULL;
    }

    return node;
}

void node_tree_destroy(Node *node, void (*key_destructor)(void *), void (*value_destructor)(void *)) {
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

    for (int i = 0; i < node->keyAmt; i++) {
        node_tree_destroy(node->childNodes[i], key_destructor, value_destructor);
    }

    free(node->keys);
    free(node->values);
    free(node->childNodes);
    free(node);
}

void node_insert(Node *node, void *key, void *value, int (*key_cmp)(void *, void *)) {
    int i = node->keyAmt - 1;
    
    // Encontrar a posição correta para inserir a chave
    while (i >= 0 && key_cmp(node->keys[i], key) > 0) {
        node->keys[i + 1] = node->keys[i];      // Move chave para a direita
        node->values[i + 1] = node->values[i];  // Move valor para a direita
        i--;
    }
    
    // Inserir na posição correta
    node->keys[i + 1] = key;
    node->values[i + 1] = value;
    node->keyAmt++;
}

int binary_search(void **arr, void *key, int lo, int hi, int (*key_cmp)(void *, void *)) {
    int mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        int cmp = key_cmp(key, arr[mid]);

        if (cmp < 0)
            hi = mid - 1;
        else if (cmp > 0)
            lo = mid + 1;
        else
            return mid;  // Encontrou a chave
    }
    return lo;  // Índice onde a chave deveria ser inserida
}

NodeIdxTuple *node_search(Node *node, void *key, int (*key_cmp)(void *, void *)) {
    int i = binary_search(node->keys, key, 0, node->keyAmt -1, key_cmp);

    if (i < node->keyAmt && key_cmp(key, node->keys[i]) == 0) {
        NodeIdxTuple *tuple = malloc(sizeof(NodeIdxTuple));
        if (!tuple) return NULL;
        tuple->node = node;
        tuple->idx = i;
        return tuple;
    }

    if (node->isLeaf) {
        return NULL;
    } else {
        return node_search(node->childNodes[i], key, key_cmp);
    }
}

int node_get_key_amt(Node *node) {
    return node->keyAmt;
}

bool is_node_leaf(Node *node) {
    return node->isLeaf;
}

int node_get_pos(Node *node) {
    return node->nodePos;
}

void *node_get_key(Node *node, int i) {
    return node->keys[i];
}

void *node_get_value(Node *node, int i) {
    return node->values[i];
}