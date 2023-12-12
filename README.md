# libyuv

## 系统

| 系统     |      |      |
| -------- | ---- | ---- |
| macos m1 |      |      |
|          |      |      |
|          |      |      |



## 下载

```baah
git clone git@github.com:lemenkov/libyuv.git
```

## 编译过程

### 问题

#### macos libyuv 编译失败 jpeg问题

```bash
Undefined symbols for architecture arm64:
  "_jpeg_CreateDecompress", referenced from:
      libyuv::MJpegDecoder::MJpegDecoder() in mjpeg_decoder.cc.o
  "_jpeg_abort_decompress", referenced from:
      libyuv::MJpegDecoder::UnloadFrame() in mjpeg_decoder.cc.o
      libyuv::MJpegDecoder::FinishDecode() in mjpeg_decoder.cc.o
  "_jpeg_destroy_decompress", referenced from:
      libyuv::MJpegDecoder::~MJpegDecoder() in mjpeg_decoder.cc.o
  "_jpeg_read_header", referenced from:
      libyuv::MJpegDecoder::LoadFrame(unsigned char const*, unsigned long) in mjpeg_decoder.cc.o
  "_jpeg_read_raw_data", referenced from:
      libyuv::MJpegDecoder::DecodeImcuRow() in mjpeg_decoder.cc.o
  "_jpeg_resync_to_restart", referenced from:
      libyuv::MJpegDecoder::MJpegDecoder() in mjpeg_decoder.cc.o
  "_jpeg_start_decompress", referenced from:
      libyuv::MJpegDecoder::StartDecode() in mjpeg_decoder.cc.o
  "_jpeg_std_error", referenced from:
      libyuv::MJpegDecoder::MJpegDecoder() in mjpeg_decoder.cc.o
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [libyuv.dylib] Error 1
make[1]: *** [CMakeFiles/yuv_shared.dir/all] Error 2
make: *** [all] Error 2
```

[参考](https://www.cnblogs.com/chaichengxun/p/15891619.html)

```rust
Undefined symbols for architecture x86_64:
  "_jpeg_CreateDecompress", referenced from:
      libyuv::MJpegDecoder::MJpegDecoder() in mjpeg_decoder.cc.o
  "_jpeg_abort_decompress", referenced from:
      libyuv::MJpegDecoder::UnloadFrame() in mjpeg_decoder.cc.o
      libyuv::MJpegDecoder::FinishDecode() in mjpeg_decoder.cc.o
  "_jpeg_destroy_decompress", referenced from:
      libyuv::MJpegDecoder::~MJpegDecoder() in mjpeg_decoder.cc.o
  "_jpeg_read_header", referenced from:
      libyuv::MJpegDecoder::LoadFrame(unsigned char const*, unsigned long) in mjpeg_decoder.cc.o
  "_jpeg_read_raw_data", referenced from:
      libyuv::MJpegDecoder::DecodeImcuRow() in mjpeg_decoder.cc.o
  "_jpeg_resync_to_restart", referenced from:
      libyuv::MJpegDecoder::MJpegDecoder() in mjpeg_decoder.cc.o
  "_jpeg_start_decompress", referenced from:
      libyuv::MJpegDecoder::StartDecode() in mjpeg_decoder.cc.o
  "_jpeg_std_error", referenced from:
      libyuv::MJpegDecoder::MJpegDecoder() in mjpeg_decoder.cc.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [libyuv.dylib] Error 1
make[1]: *** [CMakeFiles/yuv_shared.dir/all] Error 2
make[1]: *** Waiting for unfinished jobs....
```

只需要修改`CMakeLists.txt` 文件里的:

```scss
target_link_libraries( yuvconvert ${JPEG_LIBRARY} )
```

将它改为：

```cmake
target_link_libraries( ${ly_lib_shared} ${JPEG_LIBRARY} )
```

然后重新cmake && make，成功编译出libyuv.dylib，如下是已经换的cmakelist.txt，可直接复制替换

```cmake
# CMakeLists for libyuv
# Originally created for "roxlu build system" to compile libyuv on windows
# Run with -DTEST=ON to build unit tests

PROJECT ( YUV C CXX )	# "C" is required even for C++ projects
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
OPTION( TEST "Built unit tests" OFF )

SET ( ly_base_dir	${PROJECT_SOURCE_DIR} )
SET ( ly_src_dir	${ly_base_dir}/source )
SET ( ly_inc_dir	${ly_base_dir}/include )
SET ( ly_tst_dir	${ly_base_dir}/unit_test )
SET ( ly_lib_name	yuv )
SET ( ly_lib_static	${ly_lib_name} )
SET ( ly_lib_shared	${ly_lib_name}_shared )

FILE ( GLOB_RECURSE	ly_source_files ${ly_src_dir}/*.cc )
LIST ( SORT			ly_source_files )

FILE ( GLOB_RECURSE	ly_unittest_sources ${ly_tst_dir}/*.cc )
LIST ( SORT			ly_unittest_sources )

INCLUDE_DIRECTORIES( BEFORE ${ly_inc_dir} )

# this creates the static library (.a)
ADD_LIBRARY				( ${ly_lib_static} STATIC ${ly_source_files} )

# this creates the shared library (.so)
ADD_LIBRARY				( ${ly_lib_shared} SHARED ${ly_source_files} )
SET_TARGET_PROPERTIES	( ${ly_lib_shared} PROPERTIES OUTPUT_NAME "${ly_lib_name}" )
SET_TARGET_PROPERTIES	( ${ly_lib_shared} PROPERTIES PREFIX "lib" )

# this creates the conversion tool
ADD_EXECUTABLE			( yuvconvert ${ly_base_dir}/util/yuvconvert.cc )
TARGET_LINK_LIBRARIES	( yuvconvert ${ly_lib_static} )


INCLUDE ( FindJPEG )
if (JPEG_FOUND)
  include_directories( ${JPEG_INCLUDE_DIR} )
  target_link_libraries( ${ly_lib_shared} ${JPEG_LIBRARY} )
  add_definitions( -DHAVE_JPEG )
endif()

if(TEST)
  find_library(GTEST_LIBRARY gtest)
  if(GTEST_LIBRARY STREQUAL "GTEST_LIBRARY-NOTFOUND")
    set(GTEST_SRC_DIR /usr/src/gtest CACHE STRING "Location of gtest sources")
    if(EXISTS ${GTEST_SRC_DIR}/src/gtest-all.cc)
      message(STATUS "building gtest from sources in ${GTEST_SRC_DIR}")
      set(gtest_sources ${GTEST_SRC_DIR}/src/gtest-all.cc)
      add_library(gtest STATIC ${gtest_sources})
      include_directories(${GTEST_SRC_DIR})
      include_directories(${GTEST_SRC_DIR}/include)
      set(GTEST_LIBRARY gtest)
    else()
      message(FATAL_ERROR "TEST is set but unable to find gtest library")
    endif()
  endif()

  add_executable(libyuv_unittest ${ly_unittest_sources})
  target_link_libraries(libyuv_unittest ${ly_lib_name} ${GTEST_LIBRARY})
  find_library(PTHREAD_LIBRARY pthread)
  if(NOT PTHREAD_LIBRARY STREQUAL "PTHREAD_LIBRARY-NOTFOUND")
    target_link_libraries(libyuv_unittest pthread)
  endif()
  if (JPEG_FOUND)
    target_link_libraries(libyuv_unittest ${JPEG_LIBRARY})
  endif()

  if(NACL AND NACL_LIBC STREQUAL "newlib")
    target_link_libraries(libyuv_unittest glibc-compat)
  endif()
endif()


# install the conversion tool, .so, .a, and all the header files
INSTALL ( PROGRAMS ${CMAKE_BINARY_DIR}/yuvconvert			DESTINATION bin )
INSTALL ( TARGETS ${ly_lib_static}						DESTINATION lib )
INSTALL ( TARGETS ${ly_lib_shared} LIBRARY				DESTINATION lib RUNTIME DESTINATION bin )
INSTALL ( DIRECTORY ${PROJECT_SOURCE_DIR}/include/		DESTINATION include )

# create the .deb and .rpm packages using cpack
INCLUDE ( CM_linux_packages.cmake )


```

### 编译

> 完成上述 macos libyuv 编译失败 jpeg问题 的cmaklist.txt替换

[参考](https://gitcode.com/mirrors/lemenkov/libyuv/blob/main/docs/getting_started.md#:~:text=Building%20the-,library,-with%20cmake)

```bash
mkdir out
cd out
cmake ..
cmake --build .
# 这个是我单独加的
make -j4
make install
```

