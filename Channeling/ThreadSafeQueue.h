#ifndef _THREAD_SAFE_QUEUE_
#define _THREAD_SAFE_QUEUE_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

struct elem{
    void* data;
    struct elem* next;
};
typedef struct elem elem_t;

typedef struct{
    elem_t* head;
    elem_t* tail;
    pthread_mutex_t lock;
    int curr_size;
} TSQueue;


void thread_safe_queue_init(TSQueue* tsq);

elem_t* put_together(void* e);

void enqueue(TSQueue* tsq, void* e);

void* dequeue(TSQueue* tsq);

void* front(TSQueue* tsq);

void destroy(TSQueue* tsq);












#endif