//
// Created by Chuanchao Lyu on 2023/8/24.
//

#include "zmqModels.h"
#include "TransferMessage.h"
#include "transfer_message.pb.h"
#include <iostream>

using namespace std;
using namespace utility;

zmqPub::zmqPub(zmq::context_t & io, int port) {
    _pubfut = std::async(launch::async,[this,&io,port](){return pubthread(io,port);});
}

zmqPub::~zmqPub() {
    shutdown();
}

void zmqPub::shutdown() {
    _shutdown = true;
    _buff.close();
    auto ret = _pubfut.get();
}

void zmqPub::PutInfo(const std::string & msg) {
    auto pubmsg = make_shared<transfer::infoString>();
    pubmsg->set_msg(msg);
    _buff.push(pubmsg);
}

bool zmqPub::pubthread(zmq::context_t& io,int port) {
    _logger->info("Launching zmqPub thread!");
    zmq::socket_t pubServer{io,zmq::socket_type::pub};
    string add = "tcp://*:" +to_string(port);
    pubServer.bind(add);
    while(!_shutdown){
        try{
            auto msg = _buff.waitforpop();
            if(msg.has_value()) {
                zmq::message_t pubmsg;
                GetZmqMessageFromMessage(msg.value(), pubmsg);
                pubServer.send(pubmsg,zmq::send_flags::none);
                _logger->info("pub msg");
            }
        } catch(exception& e){
            cerr<<"zmqPub::"<<__FUNCTION__<<"||"<<e.what()<<endl;
        }
    }
    this_thread::sleep_for(chrono::seconds(1));
    pubServer.close();
    return true;
}


zmqSub::zmqSub(AtomicQueue<std::shared_ptr<Message>> & buff):_buff{buff} {
}
zmqSub::~zmqSub() {
    _shutdown = true;
    auto ret = _subfut.get();
}

void zmqSub::init(zmq::context_t & io , const std::vector<std::string> & adds) {
    _subfut = std::async(launch::async,[this,&io,&adds](){return subthread(io,adds);});
}

bool zmqSub::subthread(zmq::context_t &io, const std::vector<std::string> &adds) {
    _logger->info("Launching zmqSub thread!");
    zmq::socket_t sub{io, zmq::socket_type::sub};
    for(const auto& add:adds){
        sub.connect(add.c_str());
    }
    sub.set(zmq::sockopt::subscribe,"");
    //sub.setsockopt(ZMQ_SUBSCRIBE,"",0);
    while(!_shutdown){
        try {
            zmq::message_t zmqmsg;
            if (sub.recv(zmqmsg, zmq::recv_flags::none)) {
                auto pmsg = GetMessageFromZmqMessage(zmqmsg);
                if (pmsg) {
                    //_logger->info("DataBaseManager::ListenThread,recv message name {}, count = {}",
                    //              protoMessage->GetDescriptor()->name(),++i);
                    _buff.push(pmsg);
                } else {
                    _logger->warn("subthread Failed to Parse Message");
                }
            }
        }
        catch (exception & e)
        {
            //return false;
        }
    }
    sub.close();
    _logger->info("sub thread close!");
    return true;
}





