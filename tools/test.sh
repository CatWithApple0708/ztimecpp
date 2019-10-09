#!/bin/bash
gtest_list_test=$(./gtest_runner --gtest_list_tests)
#所有的测试
testTable=""
#当前测试的模块名
curTester=""
#获取所有测试的名字，即填充testTable
for s in ${gtest_list_test[@]}; do
    # echo "$s"
    FINAL=$(echo ${s: -1})
    if [[ $FINAL == "." ]]; then
        curTester=$s
    else
        testTable="$testTable $curTester$s"
    fi
done

#执行所有的测试
for test in ${testTable[@]}; do
    ./gtest_runner --gtest_filter=$test
done
