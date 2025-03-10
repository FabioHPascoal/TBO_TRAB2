#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct Node Node;

struct NodeIdxTuple {
    Node *node;
    int idx;
};
typedef struct NodeIdxTuple NodeIdxTuple;

/*
 * Cria um novo nó
 */
Node *node_create(int t, bool isLeaf, int nodePos);

/*
 * Destroi um nó
 */
void node_tree_destroy(Node *node, void (*key_destructor)(void *), void (*value_destructor)(void *));

/*
 * Adiciona um valor e uma chave associada a um nó
 */
void node_insert(Node *node, void *key, void *value, int (*key_cmp)(void *, void *));

/*
 * Procura por uma chave específica a partir de um dado nó, percorrendo todos os filhos sucessivamente
 */
NodeIdxTuple *node_search(Node *node, void *key, int (*key_cmp)(void *, void *));

/*
 * Retorna a quantidade de chaves de um nó
 */
int node_get_key_amt(Node *node);

/*
 * Retorna se um nó é folha
 */
bool is_node_leaf(Node *node);

/*
 * Retorna a posição de um nó na árvore, considerando um percurso em level order
 */
int node_get_pos(Node *node);

/*
 * Retorna a chave de um nó
 */
void *node_get_key(Node *node, int i);

/*
 * Retorna o valor de um nó
 */
void *node_get_value(Node *node, int i);

#endif