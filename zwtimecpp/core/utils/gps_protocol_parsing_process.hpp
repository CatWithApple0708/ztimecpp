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
#include <string.h>
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
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/logger/logger_factory.hpp"

namespace zwsd {
namespace core {
using namespace std;

class GpsInfo {
 public:
  double Altitude;
  double Latitude;
  double Longitude;

  GpsInfo() {}
  double getLongitude() { return Longitude / 100; }
  double getLatitude() { return Latitude / 100; }
  double getAltitude() { return Altitude; }
};
class GpsProtocolParsingProcess {
  ENABLE_LOGGER(GpsProtocolParsingProcess);

 public:
  GpsProtocolParsingProcess();
  ~GpsProtocolParsingProcess();
  shared_ptr<GpsInfo> parseValue(string info);

 private:
  shared_ptr<GpsInfo> gpsProtocolParsing(std::string subGpsData);
  vector<std::string> gpsProtocolSegmentation(std::string gpsData);
  shared_ptr<GpsInfo> GNGGAProcess(vector<std::string> gpsData);
  shared_ptr<GpsInfo> GPGGAProcess(vector<std::string> gpsData);
};
}  // namespace core
}  // namespace zwsd