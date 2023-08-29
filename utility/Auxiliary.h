//
// Created by Chuanchao Lyu on 2022/8/13.
//

#ifndef CPP17_AUXILIARY_H
#define CPP17_AUXILIARY_H
#include <vector>
#include <string>
#include <tbb/tbb.h>
#include <boost/type_index.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <sys/utsname.h>
#include <optional>

namespace utility {

    double doAsyncChrono() noexcept;

    std::string BoostDuration();

    std::optional<std::string> getsysname();

    std::string GetCurrentWorkingDir();

    template<typename T>
    auto checktype(const T &param) {
        using boost::typeindex::type_id_with_cvr;
        return "T is " + type_id_with_cvr<T>().pretty_name() + " and parma is " +
               type_id_with_cvr<decltype(param)>().pretty_name();
    }

    std::string make_daytime_string();

    template<typename T, typename U>
    auto max(T x, U y) {
        return (x > y) ? x : y;
    }

    std::vector<std::string> Split(const std::string &str, char delim);

    template<typename T>
    std::string processPointer(T *ptr) {
        return "process Pointer is called";
    }

    template<>
    std::string processPointer(void *) = delete;

    template<>
    std::string processPointer(char *) = delete;

    int getNextID();

//auto flam = [](auto&& params){return std::forward<decltype(params)>(params)};

}
#endif //CPP17_AUXILIARY_H
