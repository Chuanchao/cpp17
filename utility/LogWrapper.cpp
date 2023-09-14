//
// Created by Chuanchao Lyu on 2022/8/14.
//

#include "LogWrapper.h"
#include <spdlog/sinks/daily_file_sink.h>
#include "Auxiliary.h"
#include <iostream>

bool LoggerInit::init(const std::string &procname, spdlog::level::level_enum level) {
    auto sysname = utility::getsysname();
    //auto username = static_cast<std::string>(getlogin());
    std::string wpath;
    if(!sysname.has_value()) return false;
    if(sysname.value() == "Linux"){
        //wpath = "/home/" + username + "/logs/";
        //wpath = "/mnt/c/Users/ChuanchaoLyu/Desktop/Algorithms/Logs/";
        wpath = "/home/otc/Logs/";
    }
    if(sysname.value() == "Darwin"){
        wpath = "/Users/chuanchao/Desktop/Programming/Logs/";
    }
    std::string filepath = wpath + procname + "/" +procname;
    auto txt_logger = spdlog::daily_logger_mt("cpp20",filepath,18);
    txt_logger->set_pattern("[%C-%m-%d %H:%M:%S.%f pid:%#{%t}]<%l> %v");
    txt_logger->set_level(level);
    txt_logger->flush_on(spdlog::level::info);
    txt_logger->info("/***********cpp20 running**************/");

    return true;

}
