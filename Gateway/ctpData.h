//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_CTPDATA_H
#define ORDERTEST_CTPDATA_H
#include <string>
#include <mutex>
#include <chrono>
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

}
#endif //ORDERTEST_CTPDATA_H
