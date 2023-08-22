aux_source_directory(. DataBaseManager_SRCS)

add_library(DataBaseManager SHARED ${DataBaseManager_SRCS})
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
    message("System is MACOS in DataBase")
    target_include_directories(DataBaseManager
            PUBLIC
            ${PROJECT_SOURCE_DIR}/utility
            /usr/local/include/mysql
            )
elseif(CMAKE_HOST_UNIX)
    message("System is Linuxin DataBase")
    set(LINUX 1)
    target_include_directories(DataBaseManager
            PUBLIC
            ${PROJECT_SOURCE_DIR}/utility
            /usr/include/mysql
            )
endif()

target_link_libraries(DataBaseManager PUBLIC mysqlpp utility)