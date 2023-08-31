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
#include <functional>
#include <unordered_map>
#include <google/protobuf/message.h>

#include "LogWrapper.h"
#include "AtomicQueue.h"

namespace utility {

    class zmqPub: private LoggerBase{
    public:
        using Message = google::protobuf::Message;
        zmqPub(zmq::context_t &, int port);
        ~zmqPub();
        void shutdown();
        void PutInfo(const std::string&);
    private:
        bool pubthread(zmq::context_t &, int port);
    private:
        std::atomic_bool _shutdown{false};
        std::future<bool> _pubfut;
        AtomicQueue<std::shared_ptr<Message>> _buff;
    };


    class zmqSub:private LoggerBase{
    public:
        using Message = google::protobuf::Message;
        explicit zmqSub(AtomicQueue<std::shared_ptr<Message>>&);
        void init(zmq::context_t& io,const std::vector<std::string>&);
        ~zmqSub();
    private:
        bool subthread(zmq::context_t&,const std::vector<std::string>&);
    private:
        std::atomic_bool _shutdown{false};
        std::future<bool> _subfut;
        AtomicQueue<std::shared_ptr<Message>>& _buff;
    };

    class msgProcessor:private LoggerBase{
    public:
        using Message=google::protobuf::Message;
        explicit msgProcessor(AtomicQueue<std::shared_ptr<Message>>&);
        ~msgProcessor();
        void rgshandles(const std::string&,std::function<void(std::shared_ptr<Message>)>);
    private:
        bool prsthread();
    private:
        std::atomic_bool _shutdown{false};
        std::future<bool> _prsfut;
        std::unordered_map<std::string,std::function<void(std::shared_ptr<Message>)>> _handles;
        AtomicQueue<std::shared_ptr<Message>>& _buff;
    };
}



#endif //ORDERTEST_ZMQMODELS_H
