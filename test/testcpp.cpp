//
// Created by Chuanchao Lyu on 2022/8/13.
//

#include "LogWrapper.h"
#include "Auxiliary.h"
#include <vector>
#include <future>
#include <unordered_map>
using namespace std;

int main(){
    DailyLogger::init("test", spdlog::level::debug);
    auto mlogger = spdlog::get("cpp17");
    auto derefless = [](const auto& p1, const auto& p2){return *p1 <*p2;};
    std::unordered_map<std::string, int> m;
    auto fut = std::async(std::launch::async,doAsyncChrono);
    std::cout<<"waiting for future!"<<std::endl;
    auto res = fut.get();
    auto x{27};
    return 0;
}
