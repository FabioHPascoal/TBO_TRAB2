
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

Deque *deque_construct();
void deque_push_back(Deque *d, int item);
void deque_push_front(Deque *d, int item);
int deque_pop_back(Deque *d);
int deque_pop_front(Deque *d);
int deque_get_size(Deque *d);
void deque_destroy(Deque *d);

#endif