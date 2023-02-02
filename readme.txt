


// კომპილაციისას მემორი ლიქ ჩექინგისთვის -Og -std=gnu99 დავამატე 
for compilation:
>make

// შემოწმებისთვის
for testing: test.c file is dedicated for each
run:
>./testTP 
or 
>./testF
or
>./testChan

// ვალგრაინდით შემოწმებისას შეიძლება კონკურენტული არ იყოს 
memory test run: 
>valgrind ./testTP 
or 
>valgrind ./testF
or
>valgrind ./testChan






//სხვა...


gcc test.c -o test
gcc ThreadPool.c -c ThreadPool
gcc test.c -o test
gcc test.c ThreadPool.o -o test
gcc test.c ThreadPool.o -lpthread -o test
gcc test.c ThreadPool.c -lpthread -o test
ctrl + c 
gcc -g -Og -std=gnu99 test.c ThreadPool.c -lpthread -o test 