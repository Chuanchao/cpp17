aux_source_directory(. DataBaseManager_SRCS)

add_library(DataBaseManager SHARED ${DataBaseManager_SRCS})
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
    message("System is MACOS in DataBase")
    set(mysql_path "/usr/local/include/mysql")
    message(${mysql_path})
elseif(CMAKE_HOST_UNIX)
    message("System is Linux in DataBase")
    set(LINUX 1)
    set(mysql_path "/usr/include/mysql")
    message(${mysql_path})
endif()

target_include_directories(DataBaseManager
        PUBLIC
        ${PROJECT_SOURCE_DIR}/utility
        ${mysql_path}
        )



target_link_libraries(DataBaseManager PUBLIC mysqlpp utility)