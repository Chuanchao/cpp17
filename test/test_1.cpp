//
// Created by Chuanchao Lyu on 2022/11/16.
//

#include <iostream>
#include "DBmysql.h"


int main(int argc, char* argv[]){
    LoggerInit::init("test1", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp17");
    /*
    std::cout<< "There are " << argc << "arguments"<<std::endl;
    for(int count=0;count<argc;count++){
        std::cout<< count << ' ' <<argv[count]<<std::endl;
    }
    */;


    std::vector<HFTrading::StockScore> ss;
    std::shared_ptr<HFTrading::DBmysql> pdb = HFTrading::DBmysql::CreateDBmysql();
    pdb->init();
    pdb->QueryShortScore("num2","20221124", ss);
    for(const auto& s:ss){
        //std::cout<<s;
        mlogger->info(s.toString());
    }
}