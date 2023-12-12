
#ifndef YUV_YUV_UTIL_H
#define YUV_YUV_UTIL_H

#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "libyuv/include/libyuv.h"
}

class yuv_util {

public:
    void fmt();
};


#endif //YUV_YUV_UTIL_H