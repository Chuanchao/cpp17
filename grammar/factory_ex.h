//
// Created by Chuanchao Lyu on 2022/11/29.
//

#ifndef CPP17_FACTORY_EX_H
#define CPP17_FACTORY_EX_H

#include <functional>
#include <memory>

class Investment{
public:
    Investment();
    virtual ~Investment();
    //copy
    Investment(Investment&);
    Investment& operator=(Investment&);
    //move
    Investment(Investment&&);
    Investment& operator=(Investment&&);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

class Stock: public Investment{};
class Bond: public Investment{};
class RealEstate: public Investment{};

using delInvmt = std::function<void(Investment*)>;
delInvmt fdelinvmt;

template<typename... Ts>
auto makeInvestment(int ty,Ts&&... params){
    std::unique_ptr<Investment,delInvmt> pInv(nullptr,fdelinvmt);
    if(ty == 1){
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if(ty ==2) {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    return pInv;
}





#endif //CPP17_FACTORY_EX_H
