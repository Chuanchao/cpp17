//
// Created by Chuanchao Lyu on 2022/12/2.
//

#ifndef CPP17_BTTIMER_H
#define CPP17_BTTIMER_H
#include <boost/asio.hpp>
#include "LogWrapper.h"
#include <optional>

namespace HFTrading{
    void reptimer();
    class Repeater:private LoggerBase{
    public:
        using Timer = boost::asio::steady_timer;
        using Server = boost::asio::io_service;
        explicit Repeater(Server&,int delay);
        ~Repeater();
        void reset(){m_count=0;}
        void repeat(int num);
    private:
        void dowork();
    private:
        Timer m_timer;
        int m_count{};
    };

    class tcpClient:private LoggerBase{
    public:
        using TCP = boost::asio::ip::tcp;
        tcpClient(boost::asio::io_service&io);
        ~tcpClient();
        bool connect(const std::string& ip="127.0.0.1", unsigned short port=8888);
        void syn_send_data(const std::string&);
        void asyn_send_data(const std::string&);
        void syn_read_data();
    private:
        //void write_handler(const boost::system::error_code&, std::size_t);
        //void read_handler(const boost::system::error_code&, std::size_t);
        std::optional<TCP::endpoint> genClientEP(const std::string& ip, unsigned short port);
    private:
        boost::asio::io_service& m_io;
        std::unique_ptr<boost::asio::io_service::work> m_work;
        TCP::socket m_socket;

    };


    class tcpServer:private LoggerBase{
    public:
        using TCP = boost::asio::ip::tcp;
        tcpServer(boost::asio::io_service&io):m_io(io), m_acceptor(m_io,TCP::v4()){};
        ~tcpServer();
        void run(unsigned short port=8888);
        void shutdown(){m_run=false;}
    private:
       TCP::endpoint genServerEP(unsigned short port);
    private:
        boost::asio::io_service& m_io;
        TCP::acceptor m_acceptor;
        std::atomic<bool> m_run{false};
        std::vector<TCP::socket> m_sockets;
        const int BACKLOG_SIZE{30};


    };
}




#endif //CPP17_BTTIMER_H
