//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_CTPDATA_H
#define ORDERTEST_CTPDATA_H
#include <string>
#include <mutex>
#include <chrono>
#include <unordered_map>
#include <condition_variable>

namespace gateway {

    struct Monitor {
        std::atomic<bool> status{false};
        std::mutex mtx;
        std::condition_variable cv;
    };
    struct UserInfo {
        std::string ip;
        int port{0};
        std::string brokerID;
        std::string userID;
        std::string password;
        std::string appid;
        std::string authcode;
    };

    struct ctpStatus {
        int frontID{0};
        int SessionID{0};
        int64_t maxorderref{0};
        std::atomic<int> requestID{0};
        std::atomic<bool> isConnected{0};
    };

    template<typename T>
    class synQuery{
    public:
       void clear(){
           _data.clear();
           _status = false;
       }
       void push(const std::string& ind ,const T& d){_data.emplace(ind,d);}
       void setfull(){_status = true;}
       auto isfull() const{return _status.load();}
       const auto& getData() const{return _data;}
    private:
        std::unordered_map<std::string,T> _data;
        std::atomic<bool> _status{false};
    };

}
#endif //ORDERTEST_CTPDATA_H
