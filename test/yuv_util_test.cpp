#include "gtest/gtest.h"
#include <iostream>
#include "yuv_util.h"


TEST(PushStreamTestSuite, PushStream) {
    std::cout << "Hello, World!" << std::endl;
    yuv_util yuvUtil;
    yuvUtil.fmt();
}