# multi-threading_library_in_C

since the C language doesn't offer a multi-threaded library of its own I implemented a Java inspired one using POSIX Threads (aka pthreads) that C does supply. this library includes thread pool, channeling, futures and promises.

// for checking memory leaks: -Og -std=gnu99  
for compilation:
>make

// testing: test.c file is dedicated for each
run:
>./testTP 
or 
>./testF
or
>./testChan

// keep in mind valgrind checks could result in loss of concurrency
memory test run: 
>valgrind ./testTP 
or 
>valgrind ./testF
or
>valgrind ./testChan




//other...

gcc test.c -o test
gcc ThreadPool.c -c ThreadPool
gcc test.c -o test
gcc test.c ThreadPool.o -o test
gcc test.c ThreadPool.o -lpthread -o test
gcc test.c ThreadPool.c -lpthread -o test
ctrl + c 
gcc -g -Og -std=gnu99 test.c ThreadPool.c -lpthread -o test 