#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct Node Node;

/*
 * Cria um novo nó
 */
Node *node_create(int t, bool isLeaf, int nodePos);

/*
 * Destroi um nó
 */
void node_destroy(Node *node, void (*key_destructor)(void *), void (*value_destructor)(void *));

#endif