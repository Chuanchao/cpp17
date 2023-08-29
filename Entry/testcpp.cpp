//
// Created by Chuanchao Lyu on 2022/8/13.
//

#include "Timer.h"
#include "CTPOrderGateway.h"
#include <iostream>

using namespace std;

int main(){
    utility::Timer t;
    LoggerInit::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp20");
    auto pgw = gateway::CTPOrderGateway::CreateCTPTradeApi();
    pgw->init("config/ctpconfig");

    mlogger->info("Time elapsed: {}",t.elapsed());
    return 0;

}
