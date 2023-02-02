#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include "semaphore.h"
#include "Future.h"

void* function1(void* promice){
    promice_t* p = (promice_t*)promice;
    printf("a new thread started doing work in the background\n");
    sleep(1);
    printf("bg job is almost done\n");
    sleep(2);
    int* i = malloc(sizeof(int)); 
    *i = 128;
    set_promice(p,(void*)i);
    printf("promice is fulfilled ready to get\n");
    return NULL;
}
int main(){
    future_t future;
    promice_t promice;
    init_future(&future, function1);
    init_promice(&promice);
    start_future(&future,&promice);

    for(int i=0; i<10; i++){
        printf("main is doing work...\n");
        sleep(1);
    }
    printf("the answer is here : %d\nyay\n", (*(int*)(get_future(&future))));
    warsuls_chabarda(&future,&promice);
    return 0;
}