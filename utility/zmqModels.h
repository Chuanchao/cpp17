//
// Created by Chuanchao Lyu on 2023/8/24.
//

#ifndef ORDERTEST_ZMQMODELS_H
#define ORDERTEST_ZMQMODELS_H

#include <zmq.hpp>
#include <thread>
#include <memory>
#include <atomic>
#include <future>
#include <google/protobuf/message.h>

#include "AtomicQueue.h"

namespace utility {

    class zmqPub {
    public:
        //static std::shared_ptr<zmqPub> CreatezmqPub(zmq::context_t&,int);
        using Message = google::protobuf::Message;

        zmqPub(zmq::context_t &, int port);

        ~zmqPub();

        void shutdown();

    private:
        bool pubthread(zmq::context_t &, int port);

    private:
        std::atomic_bool _shutdown{false};
        //zmq::context_t& _context;
        //int _port;
        std::future<bool> _pubfut;
        //std::shared_ptr<std::thread> _thread;
        AtomicQueue<std::shared_ptr<Message>> _buff;

    };

}



#endif //ORDERTEST_ZMQMODELS_H
