//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_CTPDATA_H
#define ORDERTEST_CTPDATA_H
#include <string>
#include <mutex>
#include <condition_variable>

struct Monitor{
    std::atomic<bool> _status{false};
    std::mutex _mtx;
    std::condition_variable _cv;
};
struct UserInfo{
    std::string _brokerID;
    std::string _userID;
    std::string _password;
    std::string _appid;
    std::string _authcode;
};

struct ctpStatus{
    int _frontID;
    int _SessionID;
    int64_t _maxorderref;
    std::atomic<int> _requestID;
    std::atomic<bool> _isConnected;
};


#endif //ORDERTEST_CTPDATA_H
