#include <stdlib.h>
#include <stdbool.h>
#include "BT.h"

struct BT {
    Node *root;
    int nodeAmt;
    int t;

    void (*key_destructor)(void *);
    void (*val_destructor)(void *);
    int (*key_cmp)(void *, void *);
};

BT *bt_create(int t, int (*key_cmp)(void *, void *), 
                     void (*key_destructor)(void *),
                     void (*val_destructor)(void *)) {

    BT *bt = malloc(sizeof(BT));
    if (!bt) return NULL;

    bt->root = node_create(t, true, 0);
    bt->nodeAmt = 1;
    bt->t = t;

    bt->key_destructor = key_destructor;
    bt->val_destructor = val_destructor;
    bt->key_cmp = key_cmp;

    return bt;
}

void bt_destroy(BT *bt) {
    node_tree_destroy(bt->root, bt->key_destructor, bt->val_destructor);
    free(bt);
}

// implementar: inserção quando o nó está cheio
void bt_insert(BT *bt, void *key, void *val) {
    node_insert(bt->root, key, val, bt->key_cmp);
}

NodeIdxTuple *bt_search(BT *bt, void *key) {
    return node_search(bt->root, key, bt->key_cmp);
}