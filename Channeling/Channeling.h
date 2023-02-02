#include "ThreadSafeQueue.h"
#include "semaphore.h"

typedef struct {
    sem_t sem_in;
    sem_t sem_out;
    int buffer;
    TSQueue* tsq;
    int curr_size;
} chan_t;

/**
 * @brief calls bufered_chan_init with buffer set to 1
 * 
 * @param chan memory location
 */
void chan_init(chan_t* chan);

/**
 * @brief initializes the channeling.
 * 
 * @param chan memory location
 * @param buffer element limit
 */
void buffered_chan_init(chan_t* chan, unsigned int buffer);

/**
 * @brief enqueues an element, waiting if the queue is full.
 * 
 * @param chan memory location
 * @param elem element to be enqueued 
 */
void channel_in(chan_t* chan, void* elem);

/**
 * @brief dequeues an element, waiting if the queue is empty.
 * 
 * @param chan memorry location
 * @return dequeues void* of an element 
 */
void* channel_out(chan_t* chan);

/**
 * @brief frees the allocated memory.
 * 
 * @param chan memory location
 */
void chan_destroy(chan_t* chan);
