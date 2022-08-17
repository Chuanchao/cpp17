find_package(spdlog REQUIRED)
aux_source_directory(. utility_SRCS)
add_library(utility SHARED ${utility_SRCS})
target_link_libraries(utility
        PUBLIC
            spdlog::spdlog
        )

