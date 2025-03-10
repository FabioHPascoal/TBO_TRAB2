#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "BT.h"

void value_destroy(void *value) {
    free(value);
}

void key_destroy(void *key) {
    free(key);
}

int key_cmp(void *key1, void *key2) {
    return *(int *)key1 - *(int *)key2;
}

void bt_add_random_value(BT *bt) {
    
    int *key = malloc(sizeof(int));
    *key = rand() % 100;

    int *val = malloc(sizeof(int));
    *val = rand() % 100;

    bt_insert(bt, key, val);
}

int values[] = {5, 3, 7, 2, 9};

void bt_add_value(BT *bt, int idx) {
    
    int *key = malloc(sizeof(int));
    *key = values[idx];

    int *val = malloc(sizeof(int));
    *val = values[idx];

    bt_insert(bt, key, val);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    BT *bt = bt_create(10, key_cmp, key_destroy, value_destroy);

    for (int i = 0; i < (sizeof(values)/sizeof(int)); i++) {
        bt_add_value(bt, i);
    }

    int *ptr = malloc(sizeof(int));
    *ptr = 150;
    
    NodeIdxTuple *tuple = bt_search(bt, ptr);
    printf("%d\n", tuple->idx);
    free(tuple);
    free(ptr);

    bt_destroy(bt);

    return 0;
}