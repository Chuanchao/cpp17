find_package(Protobuf REQUIRED)

if (Protobuf_FOUND)
    message("Protobuf FOUND")
    #message(${Protobuf_INCLUDE_DIR})
endif()

aux_source_directory(. protofile_SRCS)
add_library(protofile SHARED ${protofile_SRCS})

target_link_libraries(protofile
        PUBLIC
        protobuf::libprotobuf)