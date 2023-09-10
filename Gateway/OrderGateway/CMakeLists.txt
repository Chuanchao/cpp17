aux_source_directory(. ordergateway_SRCS)
add_library(OrderGateway SHARED ${ordergateway_SRCS} tradeSpi.cpp tradeSpi.h)

target_include_directories(OrderGateway
        PUBLIC
        ${PROJECT_SOURCE_DIR}/utility
        ${PROJECT_SOURCE_DIR}/Gateway
        ${PROJECT_SOURCE_DIR}/Gateway/ctp_linux
        )
target_link_directories(OrderGateway
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Gateway/ctp_linux
        )
target_link_libraries(OrderGateway
        PUBLIC
        utility
        thosttraderapi_se
        )