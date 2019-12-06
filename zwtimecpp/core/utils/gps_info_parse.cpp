#include "zwtimecpp/core/utils/gps_info_parse.hpp"
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
#include "zwtimecpp/core/utils/better-enums/enum.h"
#include "zwtimecpp/core/utils/nod/nod.hpp"
#include "zwtimecpp/core/utils/string_utils.hpp"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"
using namespace std;
using namespace zwsd;
using namespace core;

void GpsInfoParser::parseGpsInfo(string raw) {
  buf += raw;

  // 1. 找到/r/n
  // 2. 取出/r/n前面的字符串
  while (true) {
    size_t pos = buf.find_first_of("\r\n", 0);
    if (pos != string::npos) {
      string eachline(buf.begin(), buf.begin() + pos);
      buf = string(buf.begin() + pos + 2, buf.end());
      try {
        processEachLine(eachline);
      } catch (const std::exception& e) {
        logger->error("GpsInfoParser::processEachLine catch exception {}",
                      e.what());
      }
    } else {
      return;
    }
  }
}
//   nod::signal<void(gps::GPSInfo& info)> signalOnGpsInfo;

void GpsInfoParser::processEachLine(string& eachline) {
  // 4. 按照,分离
  vector<string> each = StringUtils::splitByStrDelim(eachline, ",");

#if 0
    //调试打印
    logger->info("{}", eachline);
    for (unsigned i = 0; i < each.size(); ++i)
      logger->info("{} {}", i, each[i]);
#endif

  // 5. 判断类型
  if (each.size() <= 0) return;
  UP_packet_container_t UP_packet_container;
  gps::GPSInfo gpsinfo;

    if (each[0] == "$GNGGA") {
        gpsinfo.type = gps::GPSType_t::GNGGA;

      if (!each[2].empty() && !each[3].empty())
        each[3] == "N" ? gpsinfo.data.GNGGA.lat = std::stof(each[2])/100
                       : gpsinfo.data.GNGGA.lat = -std::stof(each[2])/100;

      if (!each[4].empty() && !each[5].empty())
        each[5] == "E" ? gpsinfo.data.GNGGA.lon = std::stof(each[4])/100
                       : gpsinfo.data.GNGGA.lon = -std::stof(each[4])/100;

      if (!each[9].empty()) gpsinfo.data.GNGGA.elv = std::stof(each[9]);

      signalOnGpsInfo(gpsinfo);
    }
}
