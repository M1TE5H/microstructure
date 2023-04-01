#!/usr/bin/zsh

# Automation for Local Environment

# ================================================================

# variables
CMAKE_NEW=false

BUILD_DIR=build
APP_DIR=applications
MAIN_EXE=metal

LOCAL_C_COMPILER_PATH=/opt/local/bin/gcc-mp-11
LOCAL_CXX_COMPILER_PATH=/opt/local/bin/g++-mp-11

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

# execute
./$APP_DIR/$MAIN_EXE