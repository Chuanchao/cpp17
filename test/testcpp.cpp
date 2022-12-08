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
using namespace std;

int main(){
    Timer t;
    LoggerInit::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp17");
    auto val = 10;
    //boost::asio::io_service io;
    //HFTrading::Repeater rep(io,1);
    //rep.repeat(5);
    //io.run();
    HFTrading::reptimer();

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
