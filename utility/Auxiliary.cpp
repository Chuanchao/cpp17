//
// Created by Chuanchao Lyu on 2022/8/13.
//

#include "Auxiliary.h"
#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

double doAsyncChrono() noexcept{
    using namespace std::literals;
    auto start = std::chrono::high_resolution_clock::now();
    auto id = std::this_thread::get_id();
    std::this_thread::sleep_for(2000ms);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout <<"on thread "<<id<< " Waited " << elapsed.count() << " ms\n";
    return elapsed.count();
}


std::string BoostDuration(){
    using T = boost::chrono::time_point<boost::chrono::steady_clock,
            boost::chrono::duration<double, boost::ratio<3600> > >;
    T tp = boost::chrono::steady_clock::now();
    std::ostringstream so;
    so<<tp;
    return so.str();
}

std::string make_daytime_string(){
    time_t now = time(0);
    return ctime(&now);
}

std::vector<std::string> Split(const std::string& str, char delim){
    std::vector<std::string> items;
    std::stringstream ss(str);
    std::string item;
    while(getline(ss, item, delim))
    {
        items.push_back(item);
    }
    return items;
}

int getNextID(){
    static int id = 0;
    return ++id;
}

