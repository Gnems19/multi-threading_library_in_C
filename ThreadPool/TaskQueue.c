#include "TaskQueue.h"

/**
 * -----------------------------
 * TaskQueue - A doubly linked list implementation of a Queue
 * 
 * use:
 * - to store function argument pairs for the thread pool
 * -----------------------------
*/

void TaskQueueInit(TaskQueue* tq){
    // tqs memory is handled by the client 
    tq->head=NULL;
    tq->tail=NULL;
    tq->currSize = 0;
    
}

task_t* putTogether(thread_fn_t fu, void* arg){
    task_t* task = malloc(sizeof(task_t));  
    task->arg = arg;
    task->thread_fn = fu;
    task->next = NULL;
    task->prev = NULL;
}

void enqueue(TaskQueue* tq, task_t* task){
    assert(tq!=NULL);
    assert(task!=NULL);
    tq->currSize++;
    if(tq->head==NULL){
        tq->head = task;
        tq->tail = task;
    }else{
        tq->tail->next = task;
        task->prev = tq->tail;
        tq->tail = task;
    }
}

task_t* front(TaskQueue* tq){
    assert(tq!=NULL);
    return tq->head;
}

void dequeue(TaskQueue* tq){ 
    assert(tq!=NULL);
    assert(tq->currSize>0);
    tq->currSize--;
    task_t* task = tq->head;
    tq->head = tq->head->next;
    
    //printf("dequeue was sucsessful");
    free(task); 
}

