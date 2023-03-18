#!/usr/bin/zsh

# variables
build_dir=build
main_exe=applications/metal

# build
rm -rf $build_dir
mkdir $build_dir && cd $build_dir
cmake -DCMAKE_C_COMPILER=/opt/local/bin/gcc-mp-11 -DCMAKE_CXX_COMPILER=/opt/local/bin/g++-mp-11 ..
make

# execute
./$main_exe