//
// Created by zhaohe on 19-10-5.
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
using namespace std;
/**
 * @brief 串口协议硬件操作包参数
 */
class UartHardwareOperateParameter {
 public:
  vector<uint8_t> value;
};
/**
 * @brief 串口协议，硬件操作包
 */
class UartHardwareOperatePacket {
 public:
  uint16_t moduleType;
  uint8_t moduleNum;
  uint16_t modulerDataPoint;
  uint8_t operateCode;
  uint8_t serialNum;
  uint8_t route = 0;

  vector<UartHardwareOperateParameter> prameter;
};
}
