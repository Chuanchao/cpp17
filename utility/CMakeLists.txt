aux_source_directory(. utility_SRCS)
find_package(Boost COMPONENTS random chrono REQUIED)
find_package(spdlog REQUIRED)
find_package(TBB REQUIRED)
find_package(cppzmq REQUIRED)
add_library(utility SHARED ${utility_SRCS})
target_link_libraries(utility
        PUBLIC
        spdlog::spdlog
        Boost::random
        Boost::chrono
        TBB::tbb
        cppzmq
        )

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
    message("System is MACOS in utility")
elseif(CMAKE_HOST_UNIX)
    message("System is Linux in utility")
    set(LINUX 1)
endif()

#if(MACOS)
#    message("System is MACOS in utility")
#endif()

