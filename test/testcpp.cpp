//
// Created by Chuanchao Lyu on 2022/8/13.
//

#include "LogWrapper.h"
#include "Auxiliary.h"
#include "Timer.h"
#include "grammar.h"
#include <iostream>
#include "bttimer.h"
#include <boost/asio.hpp>
#include "ThreadPool.h"
using namespace std;

int main(){
    Timer t;
    LoggerInit::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp17");
    std::vector<int> v;
    std::iota(v.begin(),v.end(),0);

    auto val = 10;
    auto l1 = [](){this_thread::sleep_for(chrono::seconds(5));return 5;};
    auto l2 = [](){this_thread::sleep_for(chrono::seconds(10));return 10;};

    ThreadPool pools{2};
    auto f1 = pools.enqueue(l1);
    auto f2 = pools.enqueue(l2);
    mlogger->info("f1 = {}; f2 = {}",f1.get(),f2.get());

    pools.close();

    /***
    auto up = make_unique<int>(10);
    auto bigger = [p = std::move(up)](int x){cout<<*p;};
    bigger(10);
    auto derefless = [](const auto& p1, const auto& p2){return *p1 <*p2;};
    auto str = checktype(27);
    mlogger->info(str);
    auto du = BoostDuration();
    mlogger->info(du);
    ***/
    mlogger->info("Time elapsed: {}",t.elapsed());
    return 0;




}
