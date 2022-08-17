//
// Created by Chuanchao Lyu on 2022/8/13.
//

#ifndef CPP17_AUXILIARY_H
#define CPP17_AUXILIARY_H
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <boost/type_index.hpp>

double doAsyncChrono() noexcept;

template<class T>
auto checktype(const T& param){
    using boost::typeindex::type_id_with_cvr;
    return type_id_with_cvr<T>().pretty_name();
}

std::vector<std::string> Split(const std::string& str, char delim);

#endif //CPP17_AUXILIARY_H
