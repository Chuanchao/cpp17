aux_source_directory(. marketfeed_SRCS)
add_library(MarketFeed SHARED ${marketfeed_SRCS})

target_include_directories(MarketFeed
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Gateway/FeedGateway
        )
target_link_libraries(MarketFeed
        PUBLIC
        FeedGateway
        )