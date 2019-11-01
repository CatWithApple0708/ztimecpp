#include "gtest/gtest.h"
#include <functional>

#include "project_mock.hpp"
#include "zwtimecpp/core/utils/nmea_wappter.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

using namespace testing;

// const char *buff[] = {
//     "$GPRMC,173843,A,3349.896,N,11808.521,W,000.0,360.0,230108,013.4,E*69\r\n",
//     "$GPGGA,111609.14,5001.27,N,3613.06,E,3,08,0.0,10.2,M,0.0,M,0.0,0000*70\r\n",
//     "$GPGSV,2,1,08,01,05,005,80,02,05,050,80,03,05,095,80,04,05,140,80*7f\r\n",
//     "$GPGSV,2,2,08,05,05,185,80,06,05,230,80,07,05,275,80,08,05,320,80*71\r\n",
//     "$GPGSA,A,3,01,02,03,04,05,06,07,08,00,00,00,00,0.0,0.0,0.0*3a\r\n",
//     "$GPRMC,111609.14,A,5001.27,N,3613.06,E,11.2,0.0,261206,0.0,E*50\r\n",
//     "$GPVTG,217.5,T,208.8,M,000.00,N,000.01,K*4C\r\n"
// };

class GtestNmeaWappter : public testing::Test {
  ENABLE_LOGGER(GtestNmeaWappter);

 public:
  NmeaWappter nmeaWappter;

 public:
  void SetUp() override {}
};

TEST_F(GtestNmeaWappter, test) {
  {
    string gpsraw =
        "$GPRMC,173843,A,3349.896,N,11808.521,W,000.0,360.0,230108,013.4,E*"
        "69\r\n";
    NmeaINFO cpyinfo;
    nmeaWappter.parseValue(gpsraw, [&](NmeaINFO info) { cpyinfo = info; });
    EXPECT_EQ(cpyinfo.isContaninLocationInfo(), false);
  }
  {
    string gpsraw =
        "$GPGGA,111609.14,5001.27,N,3613.06,E,3,08,0.0,10.2,M,0.0,M,0.0,0000*"
        "70\r\n";
    NmeaINFO cpyinfo;
    nmeaWappter.parseValue(gpsraw, [&](NmeaINFO info) { cpyinfo = info; });
    EXPECT_EQ(cpyinfo.isContaninLocationInfo(), true);
    EXPECT_EQ(cpyinfo.getAltitude(), 10.2);
    EXPECT_EQ(cpyinfo.getLatitude(), 5001.27);
    EXPECT_EQ(cpyinfo.getLongitude(), 3613.06);
  }
  {
    string gpsraw =
        "$GPGSV,2,1,08,01,05,005,80,02,05,050,80,03,05,095,80,04,05,140,80*"
        "7f\r\n";
    NmeaINFO cpyinfo;
    nmeaWappter.parseValue(gpsraw, [&](NmeaINFO info) { cpyinfo = info; });
    EXPECT_EQ(cpyinfo.isContaninLocationInfo(), false);
  }
  {
    string gpsraw =
        "$GPGSV,2,2,08,05,05,185,80,06,05,230,80,07,05,275,80,08,05,320,80*"
        "71\r\n";
    NmeaINFO cpyinfo;
    nmeaWappter.parseValue(gpsraw, [&](NmeaINFO info) { cpyinfo = info; });
    EXPECT_EQ(cpyinfo.isContaninLocationInfo(), false);
  }
  {
    string gpsraw =
        "$GPGSA,A,3,01,02,03,04,05,06,07,08,00,00,00,00,0.0,0.0,0.0*3a\r\n";
    NmeaINFO cpyinfo;
    nmeaWappter.parseValue(gpsraw, [&](NmeaINFO info) { cpyinfo = info; });
    EXPECT_EQ(cpyinfo.isContaninLocationInfo(), false);
  }
  {
    string gpsraw = "$GPVTG,217.5,T,208.8,M,000.00,N,000.01,K*4C\r\n";
    NmeaINFO cpyinfo;
    nmeaWappter.parseValue(gpsraw, [&](NmeaINFO info) { cpyinfo = info; });
    EXPECT_EQ(cpyinfo.isContaninLocationInfo(), false);
  }
}