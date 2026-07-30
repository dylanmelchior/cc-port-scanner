#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

/*
This class represents a thread pool with a custom set amount of workers.
*/
class ThreadPool {

    public: 
        
        /*
        Constructor for this thread pool. Set the stop flag to false and populate a vector of workers with threadCount amount.
        */
        ThreadPool(size_t threadCount);

        /*
        Destructor for this thread pool. Set stop flag to true, notify all workers to awake via conditional variable and join all.
        */
        ~ThreadPool();

        /*
        Submit a new task to the queue for work to be performed. Locks the queue, adds the function to the queue, then notifies one thread to awake.
        */
        void submit(std::function<void()> fx);
    
    private:
        /*
        A vector of worker threads.
        */
        std::vector<std::thread> threads;
        
        /*
        Mutex variable for locking.
        */
        std::mutex mtx;

        /*
        Conditional variable to notify workers. Think of this as a "bell" that rings when something is added to the queue or the pool is dead.
        */
        std::condition_variable cv;

        /*
        Queue of work to be done.
        */
        std::queue<std::function<void()>> queue;

        /*
        Stop condition to stop all work and join threads.
        */
        bool stop;

        /*
        An infinite loop running on each thread. More explanation on how it works in implementation file.
        */
        void worker();

};