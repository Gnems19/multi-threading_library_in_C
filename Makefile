all: testTP testF testChan

testTP: ThreadPool/test.c ThreadPool/ThreadPool.c ThreadPool/TaskQueue.c
	gcc -g -Og -std=gnu99 ThreadPool/test.c ThreadPool/ThreadPool.c ThreadPool/TaskQueue.c -lpthread -o testTP

testF: Future/test.c Future/Future.c
	gcc -g -Og -std=gnu99 Future/test.c Future/Future.c -lpthread -o testF

testChan: Channeling/test.c Channeling/ThreadSafeQueue.c Channeling/Channeling.c
	gcc -g -Og -std=gnu99 Channeling/test.c Channeling/ThreadSafeQueue.c Channeling/Channeling.c -lpthread -o testChan