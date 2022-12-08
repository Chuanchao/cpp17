//
// Created by Chuanchao Lyu on 2022/11/25.
//

#ifndef CPP17_SIMFUNCTION_H
#define CPP17_SIMFUNCTION_H

#include <memory>

template<typename T>
class simfunction;

template<typename Ret, typename... Param>
class simfunction<Ret(Param...)>{
public:
    template<typename FunctionObject>
    simfunction(FunctionObject fo):callable(std::make_unique<callable_impl<FunctionObject> >(std::move(fo))){}
    Ret operator()(Param... param){
        return callable->call(param...);
    }
    //copy constructor
    simfunction(const simfunction& sf):callable(std::move(sf.callable->clone())){}

private:
    struct callable_interface{
        virtual Ret call(Param...) = 0;
        virtual ~callable_interface() = default;
        virtual std::unique_ptr<callable_interface> clone() const = 0;
    };

    template<typename Call>
    struct callable_impl:public callable_interface{
        callable_impl(Call pcall):callable(std::move(pcall)){}
        virtual Ret call(Param... param) override {return callable(param...);}
        virtual std::unique_ptr<callable_interface> clone() const override{
            return std::make_unique<callable_impl>(*this);
        }
        Call callable;
    };

    std::unique_ptr<callable_interface> callable;
};



#endif //CPP17_SIMFUNCTION_H
