#ifndef _FUTURE_H_
#define _FUTURE_H_

#include <pthread.h>
#include "bool.h"

typedef void* (*future_fn_t)(void* arg);


typedef struct{
    pthread_mutex_t lock;
    pthread_cond_t cond;
    void* result;
    bool isfufilled;
} promice_t;

typedef struct{
    pthread_t* thread;
    future_fn_t fun;
    promice_t* p;
} future_t;

void init_future(future_t* f, future_fn_t fun); //idk

void init_promice(promice_t* p);

void start_future(future_t* f, promice_t* p);

void* get_future(future_t* f);
//idk

bool set_promice(promice_t* p, void* res);

void warsuls_chabarda(future_t* f, promice_t* p);

void enditall();














#endif