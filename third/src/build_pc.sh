#!/bin/bash
workplace=`pwd`
install_path=../pc

#获得安装路径的绝对路径
[ ! -d ${install_path} ] && mkdir -p ${install_path}
cd ${install_path} && install_path=`pwd`

target="all"
if [ ! -z $1 ];then
    target=$1
fi
echo "build ${target}"

# googletest-release-1.8.0
if [ $target == "googletest-release-1.8.0" ] || [ $target == "all" ];then
cd ${workplace}
cd googletest-release-1.8.0
[ -d "build" ] && rm -r build
mkdir build && cd build 
cmake .. -DCMAKE_INSTALL_PREFIX=${install_path}
make -j16 || exit 1
make install
fi


echo "############################################################"
echo "# Sunccess"
echo "#"