add_executable(testcpp testcpp.cpp)
add_executable(hftrading hftrading.cpp)
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

target_include_directories(hftrading
        PRIVATE
        ${PROJECT_SOURCE_DIR}/DataBase
        )
target_link_libraries(hftrading
        PRIVATE
        DataBaseManager
        utility
        )