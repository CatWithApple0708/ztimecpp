//
// Created by zhaohe on 19-8-3.
//

#pragma once
#include <stdio.h>
#include <termio.h>
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

//实时读取按键输入，不需要敲回车
static inline int scanKeyboard() {
  int in;
  struct termios new_settings;
  struct termios stored_settings;
  tcgetattr(0, &stored_settings);
  new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON);
  new_settings.c_cc[VTIME] = 0;
  tcgetattr(0, &stored_settings);
  new_settings.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &new_settings);

  in = getchar();

  tcsetattr(0, TCSANOW, &stored_settings);
  return in;
}

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
