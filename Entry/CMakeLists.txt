add_executable(testcpp testcpp.cpp)
add_executable(hftrading hftrading.cpp)
target_include_directories(testcpp
        PRIVATE
        ${PROJECT_SOURCE_DIR}/Gateway/OrderGateway
        ${PROJECT_SOURCE_DIR}/MarketFeed
)

target_link_libraries(testcpp
        PRIVATE
        OrderGateway
        MarketFeed
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