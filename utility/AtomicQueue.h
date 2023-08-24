//
// Created by Chuanchao Lyu on 2022/12/8.
//

#ifndef CPP17_ATOMICQUEUE_H
#define CPP17_ATOMICQUEUE_H

#include <queue>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <optional>
#include <thread>

template<typename T>
class AtomicQueue{
public:
    explicit AtomicQueue(){};
    AtomicQueue(const AtomicQueue& rhs){
        std::lock_guard lk{m_mtx};
        m_data = rhs.m_data;
    }
    AtomicQueue(AtomicQueue&& rhs){
        std::lock_guard lk{m_mtx};
        m_data = std::move(rhs.m_data);
    }
    AtomicQueue& operator=(const AtomicQueue&rhs){
        std::lock_guard lk{m_mtx};
        m_data = rhs.m_data;
        return *this;
    }
    AtomicQueue& operator=(AtomicQueue&& rhs){
        std::lock_guard lk{m_mtx};
        m_data = std::move(rhs.m_data);
        return *this;
    }
    ~AtomicQueue(){
       close();
    }
    void close(){
        m_stop = true;
        m_cv.notify_all();
    }
    void push(const T& val){
        std::unique_lock lk{m_mtx};
        m_data.push(val);
        m_cv.notify_all();
    }

    void push(const std::vector<T>& vals){
        std::unique_lock lk{m_mtx};
        m_data.insert(m_data.end(),vals.begin(),vals.end());
        m_cv.notify_all();
    }

    void waitforpush(const T& val, int sz){
        while(!m_stop and m_data.size() > sz){
            std::this_thread::sleep_for(std::chrono::milliseconds (500));
        }
        push(val);
    }

    std::optional<T> waitforpop(){
        std::unique_lock lk(m_mtx);
        while(!m_stop and m_data.empty()){
            m_cv.wait(lk);
        }
        if(!m_stop and m_data.size()>0){
            auto elem = m_data.front();
            m_data.pop();
            return elem;
        }else{
           return std::nullopt;
        }
    }

    std::optional<T> try_pop(){
        std::unique_lock lk(m_mtx);
        if(m_data.empty()) return std::nullopt;
        auto elem = m_data.front();
        m_data.pop();
        return elem;
    }

    bool empty() const{
        std::lock_guard lk{m_mtx};
        return m_data.empty();
    }

    size_t size() const{
        std::lock_guard lk{m_mtx};
        return m_data.size();
    }
private:
    mutable std::mutex m_mtx;
    std::atomic<bool> m_stop{false};
    std::queue<T> m_data;
    std::condition_variable m_cv;
};


#endif //CPP17_ATOMICQUEUE_H
