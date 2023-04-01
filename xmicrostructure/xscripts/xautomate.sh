#!/usr/bin/zsh

BUILD_DIR=xbuild
APP_DIR=xapplications
MAIN_EXE=xmetal

LOCAL_C_COMPILER_PATH=/opt/local/bin/gcc-mp-11
LOCAL_CXX_COMPILER_PATH=/opt/local/bin/g++-mp-11

if [[ ! -d $BUILD_DIR ]]
then
	mkdir $BUILD_DIR
fi

cd $BUILD_DIR
cmake -DCMAKE_C_COMPILER=$LOCAL_C_COMPILER_PATH -DCMAKE_CXX_COMPILER=$LOCAL_CXX_COMPILER_PATH ..
make

./${APP_DIR}/${MAIN_EXE}