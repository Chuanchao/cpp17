//
// Created by Chuanchao Lyu on 2022/8/13.
//
#include "Auxiliary.h"
#include "Timer.h"
#include "zmqModels.h"
#include "CTPOrderGateway.h"
#include <iostream>

using namespace std;

int main(){
    utility::Timer t;
    LoggerInit::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp20");
    //auto pgw = gateway::CTPOrderGateway::CreateCTPTradeApi();
    //pgw->init("config/ctpconfig");
    zmq::context_t context{1};
    auto pub = utility::zmqPub(context,7000);
    while(true){
        auto ss = utility::nowString();
        pub.PutInfo(ss);
        using namespace std::literals;
        //this_thread::sleep_for(chrono::seconds(1));
        this_thread::sleep_for(3s);
        cout<<ss<<endl;
    }

    mlogger->info("Time elapsed: {}",t.elapsed());
    return 0;

}
