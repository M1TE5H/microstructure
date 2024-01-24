#!/usr/bin/zsh

BUILD_DIR=build

LOCAL_C_COMPILER_PATH=gcc
LOCAL_CXX_COMPILER_PATH=g++
LOCAL_COMPILER_FLAGS="-std=c++23 -O3 -Ofast -march=native -mtune=native"

# ================================================================

# overwrite (as needed)
if [[ -d $BUILD_DIR && $CMAKE_NEW = true ]]
then
	echo "OVERWRITING THE EXISTING BUILD DIRECTORY @ ${BUILD_DIR}"
	rm -rf $BUILD_DIR && mkdir $BUILD_DIR
fi

# ================================================================

# create (as needed)
if [[ ! -d $BUILD_DIR ]]
then
	echo "CREATING A NEW BUILD DIRECTORY @ ${BUILD_DIR}"
	mkdir $BUILD_DIR
fi

# ================================================================

# build
cd $BUILD_DIR
cmake -DCMAKE_C_COMPILER=$LOCAL_C_COMPILER_PATH -DCMAKE_CXX_COMPILER=$LOCAL_CXX_COMPILER_PATH ..
make

# ================================================================