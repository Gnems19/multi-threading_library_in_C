#include "assert.h"
#include "ThreadSafeQueue.h"


void thread_safe_queue_init(TSQueue* tsq){
    assert(tsq!=NULL);
    tsq->curr_size = 0;
    tsq->head = NULL;
    tsq->tail = NULL;
    pthread_mutex_init(&(tsq->lock),NULL);
}

elem_t* put_together(void* e){
    elem_t* newelem = malloc(sizeof(elem_t)); 
    newelem->data = e;
    newelem->next = NULL;
    return newelem;
}
void enqueue(TSQueue* tsq, void* e){
    assert(tsq!=NULL);
    assert(e!=NULL);

    elem_t* newelem = put_together(e);

    pthread_mutex_lock(&(tsq->lock));

    tsq->curr_size++;

    if(tsq->head == NULL){
        tsq->head = newelem;
        tsq->tail = newelem;
    }else{
        tsq->tail->next = newelem;
        tsq->tail = tsq->tail->next;
    }

    pthread_mutex_unlock(&(tsq->lock));
}

void* dequeue(TSQueue* tsq){
    assert(tsq!=NULL);
    assert(tsq->head!=NULL);

    pthread_mutex_lock(&(tsq->lock));

    elem_t* old = tsq->head;
    void* data = old->data;
    tsq->head = tsq->head->next;

    free(old); //

    tsq->curr_size--;

    pthread_mutex_unlock(&(tsq->lock));
    return data;
}

void* front(TSQueue* tsq){
    assert(tsq!=NULL);
    assert(tsq->curr_size>0);
    pthread_mutex_lock(&(tsq->lock));
    void* data = tsq->head->data;
    pthread_mutex_unlock(&(tsq->lock));
    return data;
}

void destroy(TSQueue* tsq){
    while(tsq->curr_size>0){
        dequeue(tsq);
    }
    pthread_mutex_destroy(&(tsq->lock));
}