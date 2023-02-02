#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include "semaphore.h"
#include "ThreadPool.h"
//bool stop;
/*void* thread_function(void* arg){
    while(true){
        if(!stop)
            printf("%d working...\n", *((int*)arg));
        else return NULL;
        sleep(1);
    }
}*/
int NUM_TESTS = 109;
int numdone = 0;
int test_passed = 0;

void* thread_function1(void* arg){
    printf(">>>>>>>>>>> start F1 <<<<<<<<<<<<\n");
    int sum=0;
    for(int i=0; i<*((int*)arg)*10000000; i++)
        sum+=i;
    printf("---------------F1 done-------------- \n ans = %d\n\n", sum);
    if(sum == 1250212352)
        test_passed++;
    numdone++;
}

void* thread_function2(void* arg){
    printf(">>>>>>>>>>> start F2 <<<<<<<<<<<<\n");
    sleep(1);
    printf("almost done...\n");
    sleep(1);
    printf("---------------F2 done-------------- \n");
    test_passed++;
    numdone++;
}

int main(){
    ThreadPool pool;
    ThreadPoolInit(&pool, 16);
    int a = 120;
    void* argumentoo = &a;

    //scheduling 16 times
    for(int i=0; i<16; i++)
        ThreadPoolSchedule(&pool,thread_function1,argumentoo);

    //scheduling "hard work" 3 times
    for(int i=0; i<3; i++)
        ThreadPoolSchedule(&pool,thread_function2,NULL);

    //scheduling 30 times
    for(int i=0; i<30; i++)
        ThreadPoolSchedule(&pool,thread_function1,argumentoo);
    //scheduling 30 times
    for(int i=0; i<30; i++)
        ThreadPoolSchedule(&pool,thread_function1,argumentoo);
    //scheduling 30 times
    for(int i=0; i<30; i++)
        ThreadPoolSchedule(&pool,thread_function1,argumentoo);

    ThreadPoolShutdown(&pool);

    //printf("%d\n", pool.ScheduledWork->currSize);
    printf("main ended numdone == %d\n",numdone);
    printf("passed %d/%d\n",test_passed,NUM_TESTS);
    
    return 0;
}