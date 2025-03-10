#ifndef BT_H
#define BT_H

#include <stdbool.h>
#include "node.h"

typedef struct BT BT;

/*
 * Cria um nova árvore B
 */
BT *bt_create(int t, int (*key_cmp)(void *, void *), 
                     void (*key_destructor)(void *),
                     void (*val_destructor)(void *));

void bt_destroy(BT *bt);

void bt_insert(BT *bt, void *key, void *val);

NodeIdxTuple *bt_search(BT *bt, void *key);

#endif