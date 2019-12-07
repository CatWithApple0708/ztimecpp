#include "gtest/gtest.h"
#include <functional>

#include "project_mock.hpp"
#include "zwtimecpp/core/utils/gps_info_parse.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

using namespace testing;

class GtestGpsInfoPraser : public testing::Test {
  ENABLE_LOGGER(GtestGpsInfoPraser);

 public:
  void SetUp() override { logger->set_level(level::debug); }
};

string testData =
    "$GNGGA,092816.000,4004.70688,N,11620.94554,E,1,12,0.9,30.8,M,0.0,M,,*"
    "4B\r\n"
    "$GNGLL,4004.70688,N,11620.94554,E,092816.000,A,A*4F\r\n"
    "$GPGSA,A,3,03,16,22,26,29,31,32,33,,,,,1.9,0.9,1.7*3D\r\n"
    "$BDGSA,A,3,07,09,10,14,,,,,,,,,1.9,0.9,1.7*2E\r\n"
    "$GPGSV,3,1,10,03,28,297,40,14,74,132,,16,31,215,37,22,31,272,47*7C\r\n"
    "$GPGSV,3,2,10,26,61,217,38,29,30,081,28,31,69,018,23,32,41,138,34*72\r\n"
    "$GPGSV,3,3,10,33,27,168,32,35,26,140,*74\r\n"
    "$BDGSV,2,1,06,02,,,35,04,,,33,07,72,213,33,09,82,300,33*6F\r\n"
    "$BDGSV,2,2,06,10,44,224,40,14,33,305,21*6F\r\n"
    "$GNRMC,092816.000,A,4004.70688,N,11620.94554,E,0.00,0.00,061219,,,A*75\r\n"
    "$GNVTG,0.00,T,,M,0.00,N,0.00,K,A*23\r\n"
    "$GNZDA,092816.000,06,12,2019,00,00*43\r\n"
    "$GPTXT,01,01,01,ANTENNA OK*35\r\n";

TEST_F(GtestGpsInfoPraser, test) {
  GpsInfoParser gpsInfoParser;
  bool GNGGAFlag = false;
  gpsInfoParser.signalOnGpsInfo.connect([&](gps::GPSInfo& info) {
    if (info.type == +gps::GPSType_t::GNGGA) {
      GNGGAFlag = true;
      EXPECT_FLOAT_EQ(info.data.GNGGA.lat, 40.0470688);
      EXPECT_FLOAT_EQ(info.data.GNGGA.lon, 116.2094554);
      EXPECT_FLOAT_EQ(info.data.GNGGA.elv, 30.8);
    }

    logger->info("{}", info.type._to_string());
  });
  gpsInfoParser.parseGpsInfo(testData);
}