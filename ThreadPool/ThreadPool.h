#ifndef _THREADPOOL_
#define _THREADPOOL_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "semaphore.h"
#include "TaskQueue.h"
#include "bool.h"

typedef struct
{
    TaskQueue *ScheduledWork;
    pthread_mutex_t work_lock;
    pthread_cond_t work_cond;
    pthread_cond_t all_resting_cond;
    pthread_t *workers;
    int n_resting;
    int n_workers;
    bool Shutdown;
} ThreadPool;

/**
 * inits the thread pool
*/
void ThreadPoolInit(ThreadPool *pool, int poolSize);

/**
 * puts some work in the queue if the pool is active
 * returns true if the schedule was successful, false otherwise
*/
bool ThreadPoolSchedule(ThreadPool *pool, void *fn, void *arg);

/**
 * waits all threads to finish and destroies all 
*/
void ThreadPoolShutdown(ThreadPool *pool);

/**
 * waits untill all the workers finish their tasks,
 * in other words untill the thread pool is empty
*/
void ThreadPoolWait(ThreadPool *pool);
#endif