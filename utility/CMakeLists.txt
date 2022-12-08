find_package(spdlog REQUIRED)
find_package(Boost COMPONENTS random chrono REQUIED)
find_package(TBB REQUIRED)
aux_source_directory(. utility_SRCS)
add_library(utility SHARED ${utility_SRCS})
target_link_libraries(utility
        PUBLIC
            spdlog::spdlog
            Boost::random
            Boost::chrono
            TBB::tbb
        )

