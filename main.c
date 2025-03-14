#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "BT.h"

void bt_add_random_value(BT *bt) {
    
    int key = rand() % 100;
    int val = rand() % 100;

    bt_insert(bt, key, val);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    BT *bt = bt_create(4, 4, 5);
    bt_insert(bt, 6, 7);
    bt_insert(bt, 8, 9);

    bt_print(bt);

    bt_destroy(bt);

    return 0;
}