//
// Created by Chuanchao Lyu on 2022/8/14.
//

#include "LogWrapper.h"
#include <spdlog/sinks/daily_file_sink.h>

bool DailyLogger::init(const std::string &procname, spdlog::level::level_enum level) {
    std::string filepath = "/Users/chuanchao/Desktop/Programming/Logs/" + procname + "/" +procname;
    auto txt_logger = spdlog::daily_logger_mt("cpp17",filepath,18);
    txt_logger->set_pattern("[%C-%m-%d %H:%M:%S.%f pid:%#{%t}]<%l> %v");
    txt_logger->set_level(level);

    txt_logger->info("/***********cpp17 running**************/");

    return true;

}
