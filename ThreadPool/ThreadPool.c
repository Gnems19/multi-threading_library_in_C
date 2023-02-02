#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "semaphore.h"
#include "ThreadPool.h"

/**
 * notes:
 *
 * (1)
 *   HOTEL WHILE
 *   an if(statement) will not work!
 *   for example if 5 threads get a signal from 5 tasks
 *   and 4 of them finish all 5 before the last gets a turn
 *   then the last will try to dequeue thinking there is still work.
 * (1.1)
 *   n_resting is keeping track of how many threads are waiting for a task
 *   when it is time to call ThreadPoolShutdown we first have to wait untill all the workers/threads are resting.
 * (1.2)
 *   Shutdown is used to kill all threads when the time comes.
 * (2)
 *   what if there is noone to signal it?
 *   if their is work to be done then nothing shoud happen anyway,
 *   only if there is no new work added at somepoint all threads will rest (n_resting==n_workers)
 *   that would mean everything is done AND THERE WILL BE A SIGNAL.
 *
 */

/**
 * ThreadPool Implementation in C
 * ------------------------------
 */

void *working_thread(void *arg){
    // printf("a thread started working\n");
    assert(arg != NULL);
    task_t *task;
    thread_fn_t fun;
    void *argument;
    ThreadPool *tp = (ThreadPool *)arg;
    while (true){
        pthread_mutex_lock(&(tp->work_lock));

        // printf("\na thread checking work ");
        // printf(" there is %d work left\n", (tp->ScheduledWork->currSize));

        while (tp->ScheduledWork->currSize == 0 && !(tp->Shutdown)){ // *(1)
            // CHECK IN!
            tp->n_resting++;
            if (tp->n_resting == tp->n_workers)
                pthread_cond_signal(&tp->all_resting_cond);
            pthread_cond_wait(&tp->work_cond, &(tp->work_lock));
            // CHECK OUT!
            tp->n_resting--;
        }

        // printf("a thread about to start working\n");
        if (tp->Shutdown){
            pthread_mutex_unlock(&tp->work_lock);
            break;
        }

        task = front(tp->ScheduledWork);

        assert(task != NULL);
        assert(task->thread_fn != NULL);

        fun = task->thread_fn;
        argument = task->arg;

        dequeue(tp->ScheduledWork);

        pthread_mutex_unlock((&tp->work_lock));
        // printf("calling a function\n");
        fun(argument);
    }
    // printf("\n a worker has retired ><\n"); //retire
    return NULL;
}

void ThreadPoolInit(ThreadPool *pool, int poolSize){
    assert(poolSize > 0);

    // allocates space for pthread_ts
    pthread_t *workers = malloc(poolSize * sizeof(pthread_t));
    pool->workers = workers;

    // initializes a queue for tasks
    TaskQueue *tq = malloc(sizeof(TaskQueue));
    TaskQueueInit(tq);

    // other
    pool->n_resting = 0;      //*(1.1)
    pool->ScheduledWork = tq; // the task queue
    pool->n_workers = poolSize;
    pool->Shutdown = false; //*(1.2)

    pthread_cond_init(&(pool->work_cond), NULL);
    pthread_cond_init(&(pool->all_resting_cond), NULL);
    pthread_mutex_init(&(pool->work_lock), NULL);

    for (int i = 0; i < poolSize; i++){
        /**
         * the memory that was allocated for threads will be freed automatically if they are detached
         * i just have to make sure they return/die/retier.
         */
        pthread_create(&workers[i], NULL, working_thread, pool);
        pthread_detach(workers[i]);
    }
}

bool ThreadPoolSchedule(ThreadPool *pool, void *fn, void *arg){
    
    if (fn == NULL || pool == NULL || pool->Shutdown == true){
        return false;
    }

    assert(fn != NULL);
    // assert(arg!=NULL); argument can be null that's non of my buisness
    assert(pool != NULL);
    assert(pool->Shutdown != true);
    // printf("scheduled\n");

    enqueue(pool->ScheduledWork, putTogether(fn, arg));
    pthread_cond_signal(&(pool->work_cond));
    return true;
}

void ThreadPoolShutdown(ThreadPool *pool){

    ThreadPoolWait(pool); //*(2)

    pool->Shutdown = true;

    // printf("\n initiating sweet release of death...3...2...1\n");
    // all workers at once are sent to do their last job...
    pthread_cond_broadcast(&(pool->work_cond));

    pthread_cond_destroy(&(pool->all_resting_cond));
    pthread_cond_destroy(&(pool->work_cond));
    pthread_mutex_destroy(&(pool->work_lock));

    free(pool->workers);
    free(pool->ScheduledWork);
    // free(pool) is not needed because the memory is in stack created in stack
}

void ThreadPoolWait(ThreadPool *pool){

    // printf("\n by now %d threads are resting \n ------------------",pool->n_resting);

    pthread_mutex_lock(&pool->work_lock);

    while (pool->n_resting != pool->n_workers){                                                                 
        // same
        pthread_cond_wait(&pool->all_resting_cond, &pool->work_lock); //*(2)
    }

    pthread_mutex_unlock(&(pool->work_lock));
}
