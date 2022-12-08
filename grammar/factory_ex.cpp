//
// Created by Chuanchao Lyu on 2022/11/29.
//

#include "factory_ex.h"
#include <string>
#include <vector>

struct Investment::Impl{
    std::string tick;
    std::vector<double> data;
};

Investment::Investment():pImpl(std::make_unique<Impl>()) {}
Investment::~Investment()=default;
Investment::Investment(Investment &&)=default;
Investment &Investment::operator=(Investment &&)=default;

Investment::Investment(Investment& rhs):pImpl(std::make_unique<Impl>(*rhs.pImpl)) {}
Investment &Investment::operator=(Investment &rhs) {
    if(this!=&rhs){
        *pImpl = *rhs.pImpl;
    }
    return *this;
}