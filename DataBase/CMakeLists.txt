aux_source_directory(. DataBaseManager_SRCS)

add_library(DataBaseManager SHARED ${DataBaseManager_SRCS})
target_include_directories(DataBaseManager
        PUBLIC
        ${PROJECT_SOURCE_DIR}/utility
        /usr/local/include/mysql
        )
target_link_libraries(DataBaseManager PUBLIC mysqlpp utility)