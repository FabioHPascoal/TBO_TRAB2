#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct Node Node;
typedef struct NodeIdxTuple NodeIdxTuple;

struct NodeIdxTuple {
    Node *node;
    int idx;
};

Node *node_create(int t, bool isLeaf, int nodePos);

void node_destroy(Node *node);

void disk_write(FILE *file, Node *node, int t);
Node *disk_read(FILE *file, int nodeIdx, int t);

void node_insert(Node *node, int key, int value);

NodeIdxTuple *node_search(FILE *file, int t, int nodeIdx, int key);
int single_node_search(Node *node, int t, int key);

bool is_node_leaf(Node *node);

int node_get_key_amt(Node *node);
int node_get_pos(Node *node);
int node_get_key(Node *node, int idx);
int node_get_val(Node *node, int idx);
int node_get_child_pos(Node *node, int idx);

void node_set_key_amt(Node *node, int amt);
void node_set_nodePos(Node *node, int pos);
void node_set_key_val(Node *node, int key, int val, int idx);
void node_set_child_pos(Node *parentNode, int childNodePos, int idx);

#endif