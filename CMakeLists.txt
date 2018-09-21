cmake_minimum_required(VERSION 3.10)
project(playground)

set(CMAKE_CXX_STANDARD 17)

add_library(stype INTERFACE)

target_include_directories(stype INTERFACE include)

add_executable(stypetest test/main.cpp)

target_link_libraries(stypetest PRIVATE stype)
