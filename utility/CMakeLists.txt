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
        protofile
        )

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
    set(proto_path "ProtoMac")
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
    set(proto_path "ProtoLinux")
endif()
message(${proto_path})
target_include_directories(utility
        PUBLIC
        ${PROJECT_SOURCE_DIR}/${proto_path})

#if(MACOS)
#    message("System is MACOS in utility")
#endif()

