cmake_minimum_required(VERSION 3.23)
project(OrderTest)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/product)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/product)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/lib)

include_directories(
        /usr/local/include
)

link_directories(
        /usr/local/lib
)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
message(${CMAKE_MODULE_PATH})
#add_executable(cpp17 main.cpp)
#target_compile_options(cpp17 PRIVATE -Werror)
#target_compile_features(cpp17 PRIVATE cxx_std_17)
#target_include_directories(cpp17 PUBLIC${PROJECT_SOURCE_DIR}/utility)

add_subdirectory(Entry)
add_subdirectory(utility)
add_subdirectory(ProtoFile)
add_subdirectory(grammar)
add_subdirectory(DataBase)
add_subdirectory(asioboost)

message(${CMAKE_PROJECT_NAME})
#message(${CMAKE_CXX_FLAGS})
#library does not use imported target, normally defined
#message(${xxx_INCLUDE_DIRS})
#message(${xxx_LIBRARY}) point to the library path


