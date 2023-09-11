//
// Created by Chuanchao Lyu on 2022/12/2.
//

#include "bttimer.h"
#include <thread>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <boost/asio/ip/tcp.hpp>

using namespace boost::asio;

namespace HFTrading{

    void print(const boost::system::error_code& ex, steady_timer&t,int N){
        static int count = 0;
        if(count<N){
           std::cout<<count<<std::endl;
           count++;
           t.expires_at(t.expiry()+std::chrono::seconds(1));
           auto cb = [&t,N](const boost::system::error_code& ex)
                   { print(ex,t,N);};
           t.async_wait(cb);
        }
    }
    void reptimer(){
        io_service io;
        constexpr int NUM = 5;
        steady_timer timer{io,std::chrono::seconds(1)};
        auto cb = [&timer,NUM](const boost::system::error_code& ex)
                { print(ex,timer,NUM);};
        timer.async_wait(cb);
        io.run();
    }

    Repeater::Repeater(HFTrading::Repeater::Server &io, int delay):
    m_timer(io,std::chrono::seconds(delay)),m_count(0) {}

    Repeater::~Repeater() {
        _logger->info("Final count is {}", m_count);
    }

    void Repeater::repeat(int num) {
        if(m_count<num){
            dowork();
            m_count++;
            m_timer.expires_at(m_timer.expiry()+std::chrono::seconds(1));
            //m_timer.async_wait(std::bind(&Repeater::repeat,this,num));
            using Error = boost::system::error_code;
            auto cb= [this,num](const Error&ex){ repeat(num);};
            m_timer.async_wait(cb);
        }
    }
    void Repeater::dowork() {
        _logger->info("Call {}, count is {}",__PRETTY_FUNCTION__, m_count);
    }



    //tcpClient definition
    tcpClient::tcpClient(io_service &io):m_io(io), m_socket(m_io){
        m_work = std::make_unique<io_service::work>(m_io);
    }

    tcpClient::~tcpClient() {
        m_work.reset();
    }

    bool tcpClient::connect(const std::string &ip, unsigned short port) {
        auto op_ep = genClientEP(ip,port);
        if(op_ep) {
            boost::system::error_code ec;
            //synchronously operation, block the caller thread.
            m_socket.connect(op_ep.value(), ec);
            if (ec.value() != 0) {
                _logger->error("Failed to Open Client socket! {}", ec.message());
                return false;
            }
        }
        return true;
    }

    std::optional<boost::asio::ip::tcp::endpoint>
            tcpClient::genClientEP(const std::string &ip, unsigned short port) {
        using Error = boost::system::error_code;
        Error ec;
        auto ip_add = boost::asio::ip::address::from_string(ip,ec);
        if(ec.value()!=0){
            _logger->error("Invalid ip address {}",ip);
            return std::nullopt;
            //return {};
        }
        return TCP::endpoint{ip_add,port};
    }


    void tcpClient::syn_send_data(const std::string& data) {
        /*
        size_t writen_bytes = 0;
        while(writen_bytes != data.length()){
            writen_bytes += m_socket.write_some(boost::asio::buffer(data.c_str()+writen_bytes,
                                                                   data.length()-writen_bytes));
        }
         */
        boost::asio::write(m_socket,boost::asio::buffer(data));
        m_socket.shutdown(boost::asio::socket_base::shutdown_send);
        boost::asio::streambuf rep_buf;
        boost::system::error_code ec;
        boost::asio::read(m_socket,rep_buf, ec);
        if(ec == boost::asio::error::eof){
            //whole response message has been received.
        }
        else{
            throw boost::system::system_error(ec);
        }
    }

    void tcpClient::asyn_send_data(const std::string &data) {

    }

    void tcpClient::syn_read_data() {
        constexpr size_t buf_size = 100;
        //char buf[buf_size];
        //boost::asio::read(m_socket, boost::asio::buffer(buf,buf_size));
        boost::asio::streambuf buf;
        boost::asio::read_until(m_socket,buf,'\n');
        std::string message;
        std::istream input(&buf);
        std::getline(input, message);


    }

    //tcpServer Definition

    boost::asio::ip::tcp::endpoint
     tcpServer::genServerEP(unsigned short port) {
        auto ip_adds=boost::asio::ip::address_v4::any();
        return TCP::endpoint{ip_adds,port};
    }

    void tcpServer::run(unsigned short port) {
        auto eps = genServerEP(port);
        boost::system::error_code ec;
        try{
            m_acceptor.bind(eps,ec);
            //new connection requests are rejected if the queue is full.
            m_acceptor.listen(BACKLOG_SIZE);

        }
        catch(const boost::system::error_code& ec){
            _logger->error("Failed to run Server!");
            return;
        }
        m_run = true;
        while (m_run){
            //get a idle socket

            //bind to client socket
            //m_acceptor.accept(sock);
        }
    }
}

