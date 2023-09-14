//
// Created by Chuanchao Lyu on 2022/8/13.
//
#include "Auxiliary.h"
#include "Timer.h"
#include "CTPOrderGateway.h"
#include "CTPQueryGateway.h"
#include "MarketFeed.h"
#include <iostream>


using namespace std;

int main(){
    utility::Timer t;
    LoggerInit::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp20");
    mlogger->info("run {} of {} at {} {}",__func__ ,__FILE__,__DATE__,__TIME__);
    /*
    auto pmf = make_shared<gateway::MarketFeed>();
    pmf->init("config/ctpconfig");

    std::vector<string> insts{"CF401"};
    pmf->Subscribe(insts);

    using namespace std::literals;
    this_thread::sleep_for(30s);

    auto pfd = gateway::CTPFeedGateway::CreateCTPFeedApi();
    pfd->init("config/ctpconfig");

    auto pgw = gateway::CTPOrderGateway::CreateCTPTradeApi();
    pgw->init("config/ctpconfig");
    */
    auto pqy = gateway::CTPQueryGateway::CreateCTPQueryApi();
    pqy->init("config/ctpconfig");
    //auto insts = pqy->QueryInstruments();
    auto poses = pqy->QueryPosition();
    for(const auto&item:poses){
        mlogger->info("today amount is {}",item.second.DebugString());
    }
    /*
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
    */

    mlogger->info("Time elapsed: {}",t.elapsed());
    return 0;

}
