project(util)

set(HEADER_FILES
        yuv_util.h
)

set(SOURCE_FILES
        yuv_util.cpp
)


add_library(util STATIC ${SOURCE_FILES} ${HEADER_FILES})


target_include_directories(util PUBLIC .)
# 添加libyuv.a静态库
include_directories(../libyuv/out)
link_directories(../libyuv/out)
# 将静态库连接给 add_library(yuv_util 用
target_link_libraries(util /Users/yaohua/c_workspace/yuv_util/libyuv/out/libyuv.a)