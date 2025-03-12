#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

struct Deque{
    int *arr;
    int start;
    int end;
    int size;
    int allocated;
};

Deque *deque_construct(){
    Deque *d = (Deque *)calloc(1, sizeof(Deque));
    d->arr = (int *)calloc(10, sizeof(int));
    d->allocated = 10;
    d->start = 0;
    d->end = 0;
    d->size = 0;
    return d;
}

void deque_push_back(Deque *d, int item){
    if(d->size == d->allocated){
        int *new_arr = (int *)calloc(d->allocated * 2, sizeof(int));

        int idx_orig, idx_dest;
        for (int i = 0; i < d->size; i++){
            idx_orig = (d->start + i) % d->allocated;
            idx_dest = i;

            new_arr[idx_dest] = d->arr[idx_orig];
        }

        free(d->arr);

        d->arr = new_arr;
        d->allocated *= 2;
        d->start = 0;
        d->end = d->size;
    }
    
    d->arr[d->end] = item;
    d->end = (d->end + 1) % d->allocated;
    d->size++;
}

void deque_push_front(Deque *d, int item){
    if(d->size == d->allocated){
        int *new_arr = (int *)calloc(d->allocated * 2, sizeof(int));

        int idx_orig, idx_dest;
        for (int i = 0; i < d->size; i++){
            idx_orig = (d->start + i) % d->allocated;
            idx_dest = i;

            new_arr[idx_dest] = d->arr[idx_orig];
        }

        free(d->arr);

        d->arr = new_arr;
        d->allocated *= 2;
        d->start = 0;
        d->end = d->size;
    }  

    d->start = (d->start + d->allocated - 1) % d->allocated;
    d->arr[d->start] = item;
    d->size++;
}

int deque_pop_back(Deque *d){
    int val = d->arr[(d->end + d->allocated - 1) % d->allocated];
    d->end = (d->end + d->allocated - 1) % d->allocated;
    d->size--;
    return val;
}

int deque_pop_front(Deque *d){
    int val = d->arr[d->start];
    d->start = (d->start + 1) % d->allocated;
    d->size--;
    return val;
}

int deque_get_size(Deque *d){
    return d->size;
}

void deque_destroy(Deque *d){
    free(d->arr);
    free(d);
}