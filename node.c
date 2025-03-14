#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node {
    bool isLeaf;
    int keyAmt;
    int nodePos;
    int *keys;
    int *values;
    int *childNodes;
};

Node *node_create(int t, bool isLeaf, int nodePos) {
    Node *node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->keyAmt = 0;
    node->isLeaf = isLeaf;
    node->nodePos = nodePos;

    node->keys = malloc(sizeof(int) * (t - 1));
    node->values = malloc(sizeof(int) * (t - 1));
    node->childNodes = malloc(sizeof(int) * t);

    if (!node->keys || !node->values || !node->childNodes) {
        free(node->keys);
        free(node->values);
        free(node->childNodes);
        free(node);
        return NULL;
    }

    return node;
}

void node_destroy(Node *node) {
    if (node == NULL) {
        return;
    }

    free(node->keys);
    free(node->values);
    free(node->childNodes);
    free(node);
}

void disk_write(FILE *file, Node *node, int t) {
    int nodeSize = sizeof(int) * (2 + (2 * (t - 1)) + t) + sizeof(bool);
    fseek(file, node->nodePos * nodeSize, SEEK_SET);

    fwrite(&node->keyAmt, sizeof(int), 1, file);
    fwrite(&node->isLeaf, sizeof(bool), 1, file);
    fwrite(&node->nodePos, sizeof(int), 1, file);
    
    fwrite(node->keys, sizeof(int), t - 1, file);
    fwrite(node->values, sizeof(int), t - 1, file);
    fwrite(node->childNodes, sizeof(int), t, file);

    fflush(file);
}

Node *disk_read(FILE *file, int nodeIdx, int t) {
    Node *node = node_create(t, true, nodeIdx);
    if (!node) return NULL;

    int nodeSize = sizeof(int) * (2 + (2 * (t - 1)) + t) + sizeof(bool);
    fseek(file, nodeIdx * nodeSize, SEEK_SET);

    fread(&node->keyAmt, sizeof(int), 1, file);
    fread(&node->isLeaf, sizeof(bool), 1, file);
    fread(&node->nodePos, sizeof(int), 1, file);

    fread(node->keys, sizeof(int), t - 1, file);
    fread(node->values, sizeof(int), t - 1, file);
    fread(node->childNodes, sizeof(int), t, file);

    return node;
}

void node_insert(Node *node, int key, int value) {
    int i = node->keyAmt - 1;

    // Find the correct position to insert the key, shifting the others to the right
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        node->values[i + 1] = node->values[i];
        i--;
    }
    
    // Insert key in the correct position
    node->keys[i + 1] = key;
    node->values[i + 1] = value;
    node->keyAmt++;
}

int binary_search(int *keys, int key, int lo, int hi) {
    int mid;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        if (key < keys[mid])
            hi = mid - 1;
        else if (key > keys[mid])
            lo = mid + 1;
        else
            return mid;  // Found the key
    }
    return lo;  // Index where the key should be
}

NodeIdxTuple *node_search(FILE *file, int t, int nodeIdx, int key) {
    Node *node = disk_read(file, nodeIdx, t);
    if (!node) return NULL;

    // Find the index of the searched key, or the index to where it should be
    int i = binary_search(node->keys, key, 0, node->keyAmt -1);

    // The key searched is in this node
    if ((i < node->keyAmt) && (key == node->keys[i])) {
        NodeIdxTuple *tuple = malloc(sizeof(NodeIdxTuple));
        if (!tuple) return NULL;

        tuple->node = node;
        tuple->idx = i;

        return tuple;
    }

    // Searched key is not in the tree
    if (node->isLeaf) {
        node_destroy(node);
        return NULL;
    }

    // Search for the key in a child node
    else return node_search(file, t, node->childNodes[i], key);
}

int single_node_search(Node *node, int t, int key) {
    int idx = binary_search(node->keys, key, 0, node->keyAmt -1);
    return idx;
}

bool is_node_leaf(Node *node) {
    return node->isLeaf;
}

int node_get_key_amt(Node *node) {
    return node->keyAmt;
}

int node_get_pos(Node *node) {
    return node->nodePos;
}

int node_get_key(Node *node, int idx) {
    return node->keys[idx];
}

int node_get_val(Node *node, int idx) {
    return node->values[idx];
}

int node_get_child_pos(Node *node, int idx) {
    return node->childNodes[idx];
}

void node_set_key_amt(Node *node, int amt) {
    node->keyAmt = amt;
}

void node_set_nodePos(Node *node, int pos) {
    node->nodePos = pos;
}

void node_set_key_val(Node *node, int key, int val, int idx) {
    node->keys[idx] = key;
    node->values[idx] = val;
}

void node_set_child_pos(Node *parentNode, int childNodePos, int idx) {
    parentNode->childNodes[idx] = childNodePos;
}