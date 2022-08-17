//
// Created by Chuanchao Lyu on 2022/8/13.
//

#ifndef CPP17_AUXILIARY_H
#define CPP17_AUXILIARY_H
#include <thread>
#include <chrono>
#include <iostream>

auto doAsyncChrono() noexcept{
    using namespace std::literals;
    auto start = std::chrono::high_resolution_clock::now();
    auto id = std::this_thread::get_id();
    std::this_thread::sleep_for(2000ms);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout <<"on thread "<<id<< " Waited " << elapsed.count() << " ms\n";
    return elapsed.count();
}



#endif //CPP17_AUXILIARY_H
