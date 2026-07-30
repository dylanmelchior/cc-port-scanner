#include "thread_pool.h"

/*
Implementation of the thread pool header file.
*/
ThreadPool::ThreadPool(size_t threadCount){
    stop = false;
    for(size_t i = 0; i < threadCount; i++){
        threads.emplace_back(&ThreadPool::worker, this);
    }
}

/*
Lock shared resource stop flag, then notify all workers (via conditional variable) to awake and join.
*/
ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(mtx);  
        stop = true;
    }

    cv.notify_all();
    for(auto& t : threads){
        t.join();
    }
}

/*
A worker thread. Infinite loop that locks the shared resource (the queue) and is put to sleep. The sleep command (wait) will unlock automatically 
when ran. When an outside source sends a notification, the lock will then activate and check the predicate (second parameter line 40). If we need to stop, 
or the queue is not empty (work to be done) then the wait command will relock the thread, and awaken. It will populate the function to be done and call it.
*/
void ThreadPool::worker(){
    for(;;) {
        std::function<void()> current_task;
        {
          std::unique_lock<std::mutex> lock(mtx);  
          
          cv.wait(lock, [this]() {
            return stop || !queue.empty();
          });

          if(stop && queue.empty()){
            break;
          }

          current_task = queue.front();
          queue.pop();
        }
        current_task();
    }
}

/*
Add work to the queue to be completed. First lock the shared resource, move the function into it (already copied in signature), then notify one worker to awaken.
*/
void ThreadPool::submit(std::function<void()> fx){
    {
        std::unique_lock<std::mutex> lock(mtx);
        queue.emplace(std::move(fx));
    }
    cv.notify_one();
}