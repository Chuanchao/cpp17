//
// Created by Chuanchao Lyu on 2023/8/24.
//

#include "zmqModels.h"
#include "TransferMessage.h"
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

bool zmqPub::pubthread(zmq::context_t& io,int port) {
    cout<<"Launching zmq class!"<<endl;
    zmq::socket_t pubServer{io,ZMQ_PUB};
    string add = "tcp://*:" +to_string(port);
    pubServer.bind(add);
    while(!_shutdown){
        try{
            auto msg = _buff.waitforpop();
            if(msg.has_value()) {
                zmq::message_t pubmessage;
                GetZmqMessageFromMessage(msg.value(), pubmessage);
                pubServer.send(pubmessage,zmq::send_flags::none);
            }
        } catch(exception& e){
            cerr<<"zmqPub::"<<__FUNCTION__<<"||"<<e.what()<<endl;
        }
    }
    this_thread::sleep_for(chrono::seconds(1));
    pubServer.close();
    return true;
}
