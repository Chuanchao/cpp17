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

void zmqPub::PutInfo(std::shared_ptr<Message> msg) {
    _buff.push(msg);
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

bool zmqSub::subthread(zmq::context_t &io, const std::vector<std::string>& adds) {
    _logger->info("Launching zmqSub thread!");
    zmq::socket_t sub{io, zmq::socket_type::sub};
    for(const auto& add:adds){
        sub.connect(add.c_str());
    }
    sub.set(zmq::sockopt::subscribe,"");
    //sub.setsockopt(ZMQ_SUBSCRIBE,"",0);
    while(!_shutdown){
        try {
            zmq::pollitem_t items[] = {{sub, 0, ZMQ_POLLIN, 0}};
            zmq::poll(&items[0], 1, std::chrono::milliseconds(5000));
            if (items[0].revents & ZMQ_POLLIN){
                zmq::message_t zmqmsg;
                auto res = sub.recv(zmqmsg, zmq::recv_flags::none);
                auto pmsg = GetMessageFromZmqMessage(zmqmsg);
                if (pmsg) {
                    //_logger->info("{}",pmsg->GetDescriptor()->full_name());
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

zmqAsynRep::zmqAsynRep(zmq::context_t &io, int port, AtomicQueue<std::shared_ptr<Message>> & buff):_buff{buff} {
    _repfut = std::async(launch::async,[this,&io,port](){return repthead(io,port);});
}

zmqAsynRep::~zmqAsynRep() {
    shutdown();
}

void zmqAsynRep::shutdown() {
    _shutdown = true;
    auto ret = _repfut.get();
}


bool zmqAsynRep::repthead(zmq::context_t &io, int port) {
    _logger->info("RepThread Launching");
    zmq::socket_t rep(io,zmq::socket_type::rep);
    rep.set(zmq::sockopt::rcvtimeo,1000);
    rep.bind("tcp://*:" +to_string(port));

    while(!_shutdown){
        try {
            zmq::pollitem_t items[] = {{rep, 0, ZMQ_POLLIN, 0}};
            zmq::poll(&items[0], 1, std::chrono::milliseconds(5000));
            if (items[0].revents & ZMQ_POLLIN){
                zmq::message_t req;
                auto res = rep.recv(req,zmq::recv_flags::none);
                auto reqmsg = GetMessageFromZmqMessage(req);
                if (reqmsg) {
                    _buff.push(reqmsg);
                }
                rep.send(req, zmq::send_flags::none);
            }
        }
        catch (exception& e){
            cerr<<__FUNCTION__<<"||"<<e.what()<<endl;
        }
    }
    rep.close();
    _logger->info("repThread Closed!");
    return true;
}


zmqSynReq::zmqSynReq(zmq::context_t &io, const std::string& add,
                     AtomicQueue<std::shared_ptr<Message>> &buff):
                     _io{io},_add{add},_buff{buff} {}
zmqSynReq::~zmqSynReq(){
    shutdown();
}

void zmqSynReq::shutdown() {
    _shutdown=true;
    auto ret = _reqfut.get();
}


std::shared_ptr<zmq::socket_t> zmqSynReq::mkreq() {
    auto req = make_shared<zmq::socket_t>(_io,zmq::socket_type::req);
    req->connect(_add);
    req->set(zmq::sockopt::linger,0);
    return req;
}

bool zmqSynReq::reqthead() {
    _logger->info("Launching reqThread");
    auto req = mkreq();

    while(!_shutdown) {
        auto msg = _buff.waitforpop();
        if(msg.has_value()){
        //_logger->info("RealTimeExecutionManager::RequestThread,Send request {}"
        //              ,msg.value()->GetDescriptor()->full_name());
            try {
                zmq::message_t reqZmq;
                GetZmqMessageFromMessage(msg.value(), reqZmq);
                req->send(reqZmq,zmq::send_flags::none);
                bool expect_reply = true;
                while (expect_reply) {
                    zmq::pollitem_t items[] = {{*req, 0, ZMQ_POLLIN, 0}};
                    zmq::poll(&items[0], 1, std::chrono::milliseconds(5000));

                    //  If we got a reply, process it
                    if (items[0].revents & ZMQ_POLLIN) {
                        zmq::message_t rspZmq;
                        auto res = req->recv(rspZmq, zmq::recv_flags::none);
                        if(res.has_value()){
                            auto repmsg = GetMessageFromZmqMessage(rspZmq);
                            if(repmsg){
                                _logger->info("{}",msg.value()->GetDescriptor()->full_name());
                            }
                        }
                        expect_reply = false;
                    } else {
                        _logger->info("W: no response from server, retrying…");
                        this_thread::sleep_for(std::chrono::seconds(5));
                        //  Old socket will be confused; close it and open a new one
                        req = mkreq();
                        //  Send request again, on new socket
                        zmq::message_t reqZmq;
                        GetZmqMessageFromMessage(msg.value(), reqZmq);
                        req->send(reqZmq,zmq::send_flags::none);
                    }
                }
            } catch (exception &e) {}
        }
    }
    _logger->info("ReqThread Close!");
    return true;
}


msgProcessor::msgProcessor(AtomicQueue<std::shared_ptr<Message>> &buff):_buff{buff} {
    _prsfut = std::async(launch::async,[this](){return prsthread();});
}
msgProcessor::~msgProcessor() {
    _shutdown = true;
    auto ret = _prsfut.get();
}

void msgProcessor::rgshandles(const std::string & name, function<void(std::shared_ptr<Message>)> fn) {
    _handles[name] = fn;
}

bool msgProcessor::prsthread() {
    _logger->info("prsThread, Launching");
    size_t count = 0;
    while (!_shutdown) {
        auto msg = _buff.waitforpop();
        if (msg.has_value()) {
            auto handler = _handles.find(msg.value()->GetDescriptor()->full_name());
            if (handler != _handles.end()) {
                handler->second(msg.value());
            }
        }
    }
    _logger->info("prsThread Closed!");
    return true;
}





