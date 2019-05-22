//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <thread>

namespace zwsd {
namespace core{
using namespace std;
/**
 * 静态方法:
 * 通过线程id知道线程是否阻塞
 * 通过线程id唤醒线程
 * 默认睡眠
 *
 * 通过线程对象获得:
 * 获得线程创建的位置
 * 抛出所有未处理的异常到异常处理中心
 * 给线程给予名字
 */
class Thread {

  public:
	Thread(std::function<void()> run);

	static void sleep();
	static void sleepForMs(int ms);
	static void yield();
};
}
}


