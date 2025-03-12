#ifndef BT_H
#define BT_H

#include <stdbool.h>
#include "node.h"

typedef struct BT BT;

BT *bt_create(int t, int firstKey, int firstVal);
void bt_destroy(BT *bt);

void bt_insert(BT *bt, int key, int val);
NodeIdxTuple *bt_search(BT *bt, int key);

void bt_print(BT *bt);

#endif