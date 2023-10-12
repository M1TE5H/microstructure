#!/usr/bin/zsh

BUILD_DIR=vbuild
MAIN_EXE=vmetal

LOCAL_C_COMPILER_PATH=${HOME}/gcc-13-build/bin/gcc
LOCAL_CXX_COMPILER_PATH=${HOME}/gcc-13-build/bin/g++
LOCAL_COMPILER_FLAGS="-std=c++23 -O3 -Ofast -march=native -mtune=native"

cd ${BUILD_DIR}

cmake -DCMAKE_OSX_SYSROOT="" \
      -DCMAKE_C_COMPILER=$LOCAL_C_COMPILER_PATH \
      -DCMAKE_CXX_COMPILER=$LOCAL_CXX_COMPILER_PATH \
      -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
      
make

./${MAIN_EXE}