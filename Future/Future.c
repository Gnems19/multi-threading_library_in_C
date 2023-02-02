#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "Future.h"


void init_future(future_t* f, future_fn_t fun){
    assert(f!=NULL);
    assert(fun!=NULL);
    f->fun = fun;
    f->p = NULL;
}

void start_future(future_t* f, promice_t* p){
    assert(f!=NULL);
    assert(p!=NULL);
    f->p = p;
    pthread_t* future_work = malloc(sizeof(pthread_t)); // needs to be freed
    f->thread = future_work;
    pthread_create(future_work,NULL,f->fun,f->p);
    pthread_detach(*future_work);
}

void* get_future(future_t* f){
    assert(f!=NULL);
    assert(f->p!=NULL);
    pthread_mutex_lock(&(f->p->lock));
    while(!f->p->isfufilled){
        printf("srr main u have to wait...\n");
        pthread_cond_wait(&(f->p->cond),&(f->p->lock));
    }
    pthread_mutex_unlock(&(f->p->lock));
    return f->p->result;
}

void init_promice(promice_t* p){
    assert(p!=NULL);
    p->result = NULL;
    p->isfufilled = false;
    pthread_cond_init(&(p->cond),NULL); //needs to be freed
    pthread_mutex_init(&(p->lock),NULL); // needs to be freed
}

bool set_promice(promice_t* p, void* res){
    assert(p!=NULL);
    pthread_mutex_lock(&(p->lock));
    if(p->isfufilled){
        pthread_mutex_unlock(&(p->lock));
        return false;  
    } 
    p->result = res;
    p->isfufilled = true;
    pthread_mutex_unlock(&(p->lock));
    pthread_cond_signal(&(p->cond));
}

void warsuls_chabarda(future_t* f, promice_t* p){
    free(f->thread); // ?
    free(p->result);
}