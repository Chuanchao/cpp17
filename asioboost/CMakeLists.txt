find_package(Boost COMPONENTS system chrono regex REQUIED)
aux_source_directory(. asio_SRCS)
add_library(basio SHARED ${asio_SRCS} ../protoLinux/TransferMessage.h)
target_include_directories(basio
        PUBLIC
        ${PROJECT_SOURCE_DIR}/utility
        )
target_link_libraries(basio
        PUBLIC
        Boost::chrono
        Boost::system
        Boost::regex
        utility
        )

