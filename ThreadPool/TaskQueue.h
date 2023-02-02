#ifndef _TASKQUEUE_
#define _TASKQUEUE_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/**
 * thread_fn_t a function that takes a void* as argument(s) and returns a void* 
*/
typedef void (*thread_fn_t)(void* arguments);

/**
 * a doubly linked lists single node
*/
struct task{
    // data
    thread_fn_t thread_fn;
    void* arg;
    // links
    struct task* next;
    struct task* prev;
};
typedef struct task task_t;

/**
 * a queue "object"
*/
typedef struct{
    task_t* head;
    task_t* tail;
    int currSize;
}TaskQueue;

/**
 *  TaskQueueInit(TaskQueue);
 * 
 * use:
 * - initalizes the queue
 * - allocatin the memory for us
*/
void TaskQueueInit(TaskQueue* tq);

/**
 * task_t* putTogether(function, argument(s));
 * 
 * use:
 * - to return a task "object" with its memory for us allocated 
*/
task_t* putTogether(thread_fn_t fu, void* arg);

/**
 * enqueue(threadpool, task);
 * 
 * use:
 * - adds a task to the queue of a given threadpool;
*/
void enqueue(TaskQueue* tq, task_t* task);

/**
 * task_t* front(TaskQueue);
 * 
 * use:
 * - peeks at what is front of a given queue and returns its pointer 
*/
task_t* front(TaskQueue* tq);

/**
 * dequeue(TaskQueue);
 * 
 * use:
 * - dequeues the element from queue
 * - frees element memory
*/
void dequeue(TaskQueue* tq);



#endif