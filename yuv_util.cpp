#include "yuv_util.h"
#include <iostream>

void yuv_util::fmt() {
    std::cout << "hello world" << std::endl;
//    std::cout << yuv::FOURCC_CM24 << std::endl;
    int width = 640;
    int height = 480;

    uint8_t *src_y = new uint8_t[width * height];
    uint8_t *src_u = new uint8_t[width * height / 4];
    uint8_t *src_v = new uint8_t[width * height / 4];

    uint8_t *dst_rgb = new uint8_t[width * height * 3];

    // 将图像数据填充为YUV格式
    for (int i = 0; i < width * height; i++) {
        src_y[i] = i % 256;
    }
    for (int i = 0; i < width * height / 4; i++) {
        src_u[i] = 0;
        src_v[i] = 128;
    }

    // 将YUV格式的图像数据转换成RGB格式的图像数据
    libyuv::I420ToBGRA(src_y, width, src_u, width / 2, src_v, width / 2,
                       dst_rgb, width * 3, width, height);

    // 输出RGB格式的图像数据
    for (int i = 0; i < 10; i++) {
        std::cout << (int) dst_rgb[i * 3] << "," << (int) dst_rgb[i * 3 + 1] << "," << (int) dst_rgb[i * 3 + 2]
                  << std::endl;
    }

    delete[] src_y;
    delete[] src_u;
    delete[] src_v;
    delete[] dst_rgb;
}
