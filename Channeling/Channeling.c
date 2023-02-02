#include "Channeling.h"

void chan_init(chan_t* chan){
    assert(chan!=NULL);
    buffered_chan_init(chan,1);
}

void buffered_chan_init(chan_t* chan, unsigned int buffer){
    chan->buffer = buffer;
    chan->curr_size = 0;
    chan->tsq = malloc(sizeof(TSQueue)); 
    thread_safe_queue_init(chan->tsq);
    sem_init(&(chan->sem_in),0,buffer);
    sem_init(&(chan->sem_out),0,0);
}

void channel_in(chan_t* chan, void* elem){
    assert(chan!=NULL);
    sem_wait(&(chan->sem_in));
    chan->curr_size++;
    enqueue(chan->tsq,elem);
    sem_post(&(chan->sem_out));
}

void* channel_out(chan_t* chan){
    assert(chan!=NULL);
    sem_wait(&(chan->sem_out));
    chan->curr_size--;
    void* data = dequeue(chan->tsq);
    sem_post(&(chan->sem_in));
    return data;
}

void chan_destroy(chan_t* chan){
    destroy(chan->tsq);
    free(chan->tsq);
    sem_destroy(&(chan->sem_in));
    sem_destroy(&(chan->sem_out));
}
