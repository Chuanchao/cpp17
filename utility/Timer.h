//
// Created by Chuanchao Lyu on 2022/11/23.
//

#ifndef CPP17_TIMER_H
#define CPP17_TIMER_H

#include <chrono>

class Timer{
public:
    void reset(){
        m_beg = Clock::now();
    }
    double elapsed() const{
        return std::chrono::duration_cast<Second>(Clock::now()-m_beg).count();
    }

private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<Clock> m_beg{Clock::now()};

};

#endif //CPP17_TIMER_H
