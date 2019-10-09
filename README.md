###如何单独编译zwtimecpp

```bash
# 编译gtest
cd third/src/
tar -xvf googletest-release-1.8.0.tar.gz
./build_pc.sh

#编译zwtimecpp
mkdir build
cmake ..
make -j8
```

###如何在其他工程中使用zwtimecpp

```cmake

include_directories(gtest的头文件路径)
link_directories(gtest的链接路径)

set(zwtimecpp_build_on_parent ON)
add_subdirectory(dep/ztimecpp)

<!-- 这里会编译出 ztimecpp zwtimecpptest 两个库-->

```