//
// Created by Chuanchao Lyu on 2022/8/13.
//

#ifndef CPP17_AUXILIARY_H
#define CPP17_AUXILIARY_H
#include <vector>
#include <string>
#include <boost/type_index.hpp>
#include <boost/chrono/chrono_io.hpp>

double doAsyncChrono() noexcept;
auto BootDuration(){
    using T = boost::chrono::time_point<boost::chrono::steady_clock,
    boost::chrono::duration<double, boost::ratio<3600> > >;
    T tp = boost::chrono::steady_clock::now();
    return tp;
}

template<class T>
auto checktype(const T& param){
    using boost::typeindex::type_id_with_cvr;
    return type_id_with_cvr<T>().pretty_name();
}
std::vector<std::string> Split(const std::string& str, char delim);
template<class T>
std::string processPointer(T* ptr){
    return "process Pointer is called";
}
template<>
std::string processPointer(void*) = delete;
template<>
std::string processPointer(char*) = delete;


#endif //CPP17_AUXILIARY_H
