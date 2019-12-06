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
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/utils/better-enums/enum.h"
#include "zwtimecpp/core/utils/nod/nod.hpp"
#include "zwtimecpp/core/utils/string_utils.hpp"
namespace zwsd {
namespace core {
using namespace std;

namespace gps {
BETTER_ENUM(GPSType_t, int, NotSet, GNGGA);

//不可以在结构体中直接赋值，这样会导致下面的共用体中无法包含此结构，
//因为共用体中会包含很多结构，每个结构的赋的初值都不一样，但由于使用的内存是同一个，因此会存在冲突
typedef struct {
  double lat; /**< Latitude in NDEG - +/-[degree][min].[sec/60] */
  double lon; /**< Longitude in NDEG - +/-[degree][min].[sec/60] */
  double
      elv; /**< Antenna altitude above/below mean sea level (geoid) in meters */
} GNGGAInfo_t;

class GPSInfo {
 public:
  GPSType_t type = GPSType_t::NotSet;
  union {
    GNGGAInfo_t GNGGA;
  } data;

 public:
  GPSInfo() { memset(&data, 0, sizeof(data)); }
};
}

class GpsInfoParser {
  ENABLE_LOGGER(GpsInfoParser)
  string buf;

 public:
  void parseGpsInfo(string raw);
  nod::signal<void(gps::GPSInfo& info)> signalOnGpsInfo;

 private:
  void processEachLine(string& eachline);
};

}  // core
}  // namespace zwsd