##如何在keil工程中使用
目前仅c代码支持在keil中使用，使用方式如下
1. 以git submodule的形式将该工程包含进keil工程中，设置路径为dep/zwtimecpp
2. 将zwtimecpp/core/utils/cutils中下的所有代码添加到keil工程中
3. 配置头文件路径为./dep/zwtimecpp/
4. 配置c的编译标准为c99
5. 在编译器配置的misc-control 中添加 --diag_suppress=1 --diag_suppress=1295 


##keil-编译器警告列表
1 文件末尾有空格
1295 当方法的参数为空时，应该添加void