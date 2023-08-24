find_package(Protobuf REQUIRED)

if (Protobuf_FOUND)
    message("Protobuf FOUND")
    #message(${Protobuf_INCLUDE_DIR})
endif()
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    aux_source_directory(../protoMac protofile_SRCS)
elseif(CMAKE_HOST_UNIX)
    aux_source_directory(../protoLinux protofile_SRCS)
endif()
add_library(protofile SHARED ${protofile_SRCS})

target_link_libraries(protofile
        PUBLIC
        protobuf::libprotobuf
        )