//
// Created by zhaohe on 19-8-3.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace zwsd {
namespace core {
using namespace std;
class CliHelp {
 public:
  /**
   * @brief 从命令读取一行指令，阻塞直到用户敲入回车
   *
   * @tparam T
   * @param deafultValue 当用户只敲入回车时，返回默认值
   * @return T
   *
   * @Usage
   * while(true){
   * 	string name;
   * 	int age;
   * 	logger->info("输入名字");
   * 	name = CliHelp().getValueFrom("defaultName");
   *    logger->info("输入年龄");
   *	age = CliHelp().getValueFrom(10);
   * }
   */
  template <typename T>
  T getValueFrom(T deafultValue) {
    T t;
    char c;
    cin.get(c);
    if (c != '\n') {
      cin.putback(c);
      cin >> t;
      cin.get();
    } else {
      t = deafultValue;
    }
    return t;
  }
};
}
}
