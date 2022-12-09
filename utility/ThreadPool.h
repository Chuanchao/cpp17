//
// Created by Chuanchao Lyu on 2022/12/8.
//

#ifndef CPP17_THREADPOOL_H
#define CPP17_THREADPOOL_H

#include "AtomicQueue.h"
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <stdexcept>



    class ThreadPool{
    public:
        ThreadPool(size_t threads)
                :_stop(false)
        {
            if(threads <= 0){
                threads = std::thread::hardware_concurrency();
            }
            _maxTasks = 100*threads;
            for (size_t i = 0; i < threads; ++i)
                _workers.emplace_back([this]{threadWork();});
        }

        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args);

        int size(){
            return _tasks.size();
        }

        void close() {
            _stop = true;
            _tasks.close();
            for (auto &t: _workers) {
                if(t.joinable()) t.join();
            }
        }

        ~ThreadPool(){
            close();
        }

    private:
        void threadWork();
    private:
        std::atomic<bool> _stop;
        std::atomic<size_t> _maxTasks;

        std::vector<std::thread> _workers;
        AtomicQueue< std::function<void()> > _tasks;

        // synchronization
        std::condition_variable _conditionEnqueue;
    };

    inline void ThreadPool::threadWork()
    {
        while(!_stop){
            auto task = _tasks.waitforpop();
            if(task){
                task.value()();
            }
        }
    }

    template<class F, class... Args>
    auto ThreadPool::enqueue(F&& f, Args&&... args)
    {
        using return_type = decltype(std::forward<F>(f)(std::forward<Args>(args)...));
        if (_stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        auto task = std::make_shared< std::packaged_task<return_type()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        _tasks.waitforpush([task]() { (*task)(); }, _maxTasks);
        return res;
    }

#endif //CPP17_THREADPOOL_H
