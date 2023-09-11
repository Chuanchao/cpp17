aux_source_directory(. feedgateway_SRCS)
add_library(FeedGateway SHARED ${feedgateway_SRCS})

target_include_directories(FeedGateway
        PUBLIC
        ${PROJECT_SOURCE_DIR}/utility
        ${PROJECT_SOURCE_DIR}/Gateway
        ${PROJECT_SOURCE_DIR}/Gateway/ctp_linux
        ${PROJECT_SOURCE_DIR}/protoLinux
        )
target_link_directories(FeedGateway
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Gateway/ctp_linux
        )
target_link_libraries(FeedGateway
        PUBLIC
        utility
        thostmduserapi
        )