#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "BT.h"

// void bt_add_random_value(BT *bt) {
    
//     int *key = malloc(sizeof(int));
//     *key = rand() % 100;

//     int *val = malloc(sizeof(int));
//     *val = rand() % 100;

//     bt_insert(bt, key, val);
// }

// int values[] = {5, 3, 7, 2, 9};

// void bt_add_value(BT *bt, int idx) {
    
//     int *key = malloc(sizeof(int));
//     *key = values[idx];

//     int *val = malloc(sizeof(int));
//     *val = values[idx];

//     bt_insert(bt, key, val);
// }

int main(int argc, char *argv[]) {
    srand(time(NULL));

    BT *bt = bt_create(3, 4, 5);

    bt_print(bt);

    bt_destroy(bt);

    return 0;
}