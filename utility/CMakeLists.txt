find_package(spdlog REQUIRED)
find_package(Boost COMPONENTS system REQUIED)
aux_source_directory(. utility_SRCS)
add_library(utility SHARED ${utility_SRCS})
target_link_libraries(utility
        PUBLIC
            spdlog::spdlog
            Boost::system
        )

