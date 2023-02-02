#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include "semaphore.h"
#include "ThreadSafeQueue.h"
#include "Channeling.h"

// for testing just fifo
void* tmp_fun(void* arg){
    TSQueue* tsq = (TSQueue*)arg;
    printf("a thread started dequeueing\n");
    for(int i=0; i<1212; i++){
        printf("1");
        dequeue(tsq);
    }
    printf("a thread finished\n");
}

void* thread_fun(void* arg){
    chan_t* chan = (chan_t*)arg;
    for(int i=0; i<20; i++){
        printf("out comes %d \n",*(int*)channel_out(chan));
    }
}
int main(){
    // tests for channeling
    int argumento = 123;
    chan_t chan;
    buffered_chan_init(&chan,1);
    pthread_t newthread;
    pthread_create(&newthread,NULL,thread_fun,&chan);
    for(int i=0; i<20; i++){
        channel_in(&chan,&argumento);
        printf("in goes %d \n",argumento);
    }
    channel_in(&chan,&argumento);
    pthread_join(newthread,NULL);
    
    chan_destroy(&chan);

    // just tested the thread safe FIFO lists
    /*
    TSQueue tsq;
    int a = 123;
    thread_safe_queue_init(&tsq);
    pthread_t newthread;
    for(int i=0; i<1212; i++){
        enqueue(&tsq,&a);
    }
    pthread_create(&newthread,NULL,tmp_fun,&tsq);
    
    for(int i=0; i<1212; i++){
        printf("0");
        enqueue(&tsq,&a);
    }
    pthread_detach(newthread);
    sleep(1);
    printf("size of tsq = %d\n", tsq.curr_size);
    destroy(&tsq);
    printf("size of tsq = %d\n", tsq.curr_size);
    pthread_join(newthread,NULL);*/
    return 0;
}
