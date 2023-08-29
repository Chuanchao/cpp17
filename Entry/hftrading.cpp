//
// Created by Chuanchao Lyu on 2022/11/16.
//

#include <iostream>
#include "DBmysql.h"
#include "Timer.h"
#include "config.h"


int main(int argc, char* argv[]){
    utility::Timer t{};
    LoggerInit::init("hftrading", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp20");
    /*
    std::cout<< "There are " << argc << "arguments"<<std::endl;
    for(int count=0;count<argc;count++){
        std::cout<< count << ' ' <<argv[count]<<std::endl;
    }
    */;

    Config config("config/ctpconfig");

    auto ip = config.pString("tdip");
    auto port = config.pInt("tdport");
    auto brokerID = config.pString("tdbrokerid");
    auto userID = config.pString("tduserid");
    auto password = config.pString("tdpassword");
    auto appid = config.pString("appid");
    auto authcode = config.pString("authcode");
    mlogger->info("{}; {} ;{}",ip,port,brokerID);



    std::vector<HFTrading::StockScore> ss;
    std::shared_ptr<HFTrading::DBmysql> pdb = HFTrading::DBmysql::CreateDBmysql();
    pdb->init();
    pdb->QueryShortScore("num2","20221124", ss);
    for(const auto& s:ss){
        std::cout<<s;
       mlogger->info(s.toString());
    }
    mlogger->info("The Program runing for {} seconds!",t.elapsed());
}