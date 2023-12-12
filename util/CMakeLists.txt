project(util)

set(HEADER_FILES
        yuv_util.h
)

set(SOURCE_FILES
        yuv_util.cpp
)


add_library(util STATIC ${SOURCE_FILES} ${HEADER_FILES})


target_include_directories(util PUBLIC .)
# 用于寻找头文件
include_directories(../libyuv/include)
# 连接库的目录
link_directories(../libyuv/out)
# 将静态库连接给 add_library(yuv_util 用
target_link_libraries(util /Users/yaohua/c_workspace/yuv_util/libyuv/out/libyuv.a)