cmake_minimum_required(VERSION 3.26)
project(yuv)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
add_subdirectory(util)



# 可以没有如下部分 作为父cmakelist.txt
add_executable(yuv main.cpp)

#include_directories(./libyuv/out)
#link_directories(./libyuv/out)
#target_link_libraries(yuv /Users/yaohua/c_workspace/yuv_util/libyuv/out/libyuv.a)