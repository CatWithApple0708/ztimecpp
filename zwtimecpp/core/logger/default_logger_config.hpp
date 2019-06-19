//
// Created by zhaohe on 19-6-18.
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

#define SET_DEFAULT_SPD_LOG_CONFIG_FILE(fileName)           \
  extern "C" {                                              \
  const std::string spdLoggerConfig() { return #fileName; } \
  }
extern "C" {
/**
 * @brief
 * logger的默认配置文件列表如下
 * 1. spd_logger_cfg.json
 * 如果不想使用默认的配置文件路径，可以实现下面的方法
 * @Demo
 *
 * const string spdLoggerConfig(){
 *  return "my_logger_cfg.json";
 * }
 *
 * @WARNING:
 *  需要注意的是，因为存在
 * static Logger_t logger=SpdLoggerFactory::createLogger(loggname);
 *
 * spdLoggerConfig方法返回值不能够动态设置，因为在程序未启动起来前这个方法就已经被使用了
 *
 * @return const string
 */

const std::string __attribute__((weak)) spdLoggerConfig();
}

