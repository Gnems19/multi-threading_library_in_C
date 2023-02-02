# multi-threading_library_in_C

this is a Java inspired multi-threading library using POSIX Threads (aka pthreads) that C supplies. this library includes thread pool, channeling, futures and promises.

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
