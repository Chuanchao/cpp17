//
// Created by Chuanchao Lyu on 2022/11/16.
//

#include <iostream>
#include "DBmysql.h"
#include "Timer.h"
#include "config.h"
#include "zmqModels.h"
#include "transfer_message.pb.h"

using namespace std::literals;

int main(int argc, char* argv[]){
    utility::Timer t{};
    LoggerInit::init("hftrading", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp20");
    /*
    std::cout<< "There are " << argc << "arguments"<<std::endl;
    for(int count=0;count<argc;count++){
        std::cout<< count << ' ' <<argv[count]<<std::endl;
    }
    std::vector<HFTrading::StockScore> ss;
    std::shared_ptr<HFTrading::DBmysql> pdb = HFTrading::DBmysql::CreateDBmysql();
    pdb->init();
    pdb->QueryShortScore("num2","20221124", ss);
    for(const auto& s:ss){
        std::cout<<s;
       mlogger->info(s.toString());
    }
    */
    zmq::context_t context{1};
    using Message = google::protobuf::Message;
    utility::AtomicQueue<shared_ptr<Message>> buffer;
    auto sub = utility::zmqSub(buffer);
    vector<string> adds;
    adds.push_back("tcp://localhost:7000");
    sub.init(context,adds);


    auto proc = utility::msgProcessor(buffer);
    auto handle = [mlogger](shared_ptr<Message> msg){
        auto pmsg = dynamic_pointer_cast<transfer::infoString>(msg);
        mlogger->info("{}",pmsg->msg());
    };
    proc.rgshandles(transfer::infoString::descriptor()->full_name(),handle);


    this_thread::sleep_for(30s);
    buffer.close();
    mlogger->info("The Program runing for {} seconds!",t.elapsed());
}