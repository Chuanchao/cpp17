#find_package(spdlog REQUIRED)
#aux_source_directory(. test_SRCS)


add_executable(testcpp testcpp.cpp)
add_executable(test1 test_1.cpp)
target_include_directories(testcpp
        PRIVATE
        ${PROJECT_SOURCE_DIR}/utility
        ${PROJECT_SOURCE_DIR}/grammar
        ${PROJECT_SOURCE_DIR}/asioboost
)
target_link_libraries(testcpp
        PRIVATE
        utility
        grammar
        basio
        )

target_include_directories(test1
        PRIVATE
        ${PROJECT_SOURCE_DIR}/DataBase
        )
target_link_libraries(test1
        PRIVATE
        DataBaseManager
        )