/**
 * @file nmea_wappter.hpp
 * @authors
 * @brief gps协议解析
 * @version 0.1
 * @date 2019-11-01
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
extern "C" {
#include "zwtimecpp/core/utils/nmealib/include/nmea/nmea.h"
}

namespace zwsd {
namespace core {
using namespace std;

class NmeaINFO {
  nmeaINFO info;

 public:
  NmeaINFO(nmeaINFO info) : info(info) {}
  NmeaINFO() { memset(&info, 0, sizeof(nmeaINFO)); }
  bool isContaninLocationInfo() {
    return (info.smask & GPGGA || info.smask & GNGGA);
  }
  double getLongitude() { return info.lon / 100; }
  double getLatitude() { return info.lat / 100; }
  double getAltitude() { return info.elv; }
};
typedef function<void(NmeaINFO info)> onGpsInfo_t;
class NmeaWappter {
  nmeaINFO nmea_info;
  nmeaPARSER nmea_parser;

 public:
  NmeaWappter();
  ~NmeaWappter();
  void parseValue(string info, onGpsInfo_t onGpsInfo);

 private:
};
}
}  // namespace zwsd