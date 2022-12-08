//
// Created by Chuanchao Lyu on 2022/8/14.
//

#ifndef CPP17_LOGWRAPPER_H
#define CPP17_LOGWRAPPER_H
#include <spdlog/spdlog.h>

class LoggerBase{
public:
    LoggerBase():_logger(spdlog::get("cpp17")){}
    std::shared_ptr<spdlog::logger> _logger;
};

class LoggerInit{
public:
    static bool init(const std::string& procname, spdlog::level::level_enum level);
};


#endif //CPP17_LOGWRAPPER_H
