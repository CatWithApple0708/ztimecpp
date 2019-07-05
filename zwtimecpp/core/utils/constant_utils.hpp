//
// Created by zhaohe on 19-7-5.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief
 * 声明一个常量,由于string,struct等类型的变量因语法上的限制，无法在头文件中以常量的形式声明，所以可以使用下面这个宏去声明
 * @Usage
 * ZWC_DECLEAR_CONSTANT(const_string,string,"const_string")
 *
 * you can use it as below
 *  printf("%s\n",const_string());
 */
#define DEFINE_CONSTANT(name, type, value) \
  static inline type Constant_##name() {                   \
    static type name##var = value;              \
    return name##var;                           \
  };

namespace zwsd {
namespace core {}
}  // namespace zwsd
