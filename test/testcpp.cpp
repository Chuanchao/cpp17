//
// Created by Chuanchao Lyu on 2022/8/13.
//

#include "LogWrapper.h"
#include "Auxiliary.h"
#include <vector>
#include <future>
#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
    DailyLogger::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp17");
    auto derefless = [](const auto& p1, const auto& p2){return *p1 <*p2;};
    auto str = checktype(27);
    mlogger->info(str);
    auto t = BootDuration();
    std::cout<<t<<std::endl;
    return 0;
}
