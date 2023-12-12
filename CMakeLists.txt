cmake_minimum_required(VERSION 3.26)
project(yuv_util)

set(CMAKE_CXX_STANDARD 14)


set(HEADER_FILES
        yuv_util.h
)

set(SOURCE_FILES
        yuv_util.cpp


)


add_library(util STATIC ${SOURCE_FILES} ${HEADER_FILES})


add_executable(yuv_util main.cpp)


include_directories(/libyuv/include)
link_directories(/libyuv/out)

target_link_libraries(yuv_util
        yuv
)