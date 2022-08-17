#find_package(spdlog REQUIRED)
aux_source_directory(. test_SRCS)


add_executable(test ${test_SRCS})
target_include_directories(test
        PRIVATE
        ${PROJECT_SOURCE_DIR}/utility
)
target_link_libraries(test PRIVATE utility)