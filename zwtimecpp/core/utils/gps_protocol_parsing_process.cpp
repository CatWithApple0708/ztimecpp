#include "gps_protocol_parsing_process.hpp"
#include "zwtimecpp/core/utils/split_worlds.hpp"
using namespace std;
using namespace zwsd;
using namespace core;
using namespace utils;

// const char *buff[] = {
//     "$GPRMC,173843,A,3349.896,N,11808.521,W,000.0,360.0,230108,013.4,E*69\r\n",
//     "$GPGGA,111609.14,5001.27,N,3613.06,E,3,08,0.0,10.2,M,0.0,M,0.0,0000*70\r\n",
//     "$GPGSV,2,1,08,01,05,005,80,02,05,050,80,03,05,095,80,04,05,140,80*7f\r\n",
//     "$GPGSV,2,2,08,05,05,185,80,06,05,230,80,07,05,275,80,08,05,320,80*71\r\n",
//     "$GPGSA,A,3,01,02,03,04,05,06,07,08,00,00,00,00,0.0,0.0,0.0*3a\r\n",
//     "$GPRMC,111609.14,A,5001.27,N,3613.06,E,11.2,0.0,261206,0.0,E*50\r\n",
//     "$GPVTG,217.5,T,208.8,M,000.00,N,000.01,K*4C\r\n"
// };

GpsProtocolParsingProcess::GpsProtocolParsingProcess() {}
GpsProtocolParsingProcess::~GpsProtocolParsingProcess(){};

shared_ptr<GpsInfo> GpsProtocolParsingProcess::parseValue(string info){
  shared_ptr<GpsInfo> gps_info;

  auto result = gpsProtocolSegmentation(info);
  for (auto var : result) {
    if (var.size() != 0) {
      gps_info = gpsProtocolParsing(var);
    }
  }
  return gps_info;
}
shared_ptr<GpsInfo> GpsProtocolParsingProcess::gpsProtocolParsing(std::string
                                                                 subGpsData) {
  // cout << "subGpsData" << subGpsData << std::endl;
  shared_ptr<GpsInfo> gps_info;
  auto subResult = split(subGpsData, ',');
  logger->debug("subResult {}", subResult[0]);
  if (subResult[0] == "GNGGA") {
    gps_info = GNGGAProcess(subResult);
  } else if (subResult[0] == "GPGGA") {
    gps_info = GPGGAProcess(subResult);
  }
  
  return gps_info;
}

vector<std::string> GpsProtocolParsingProcess::gpsProtocolSegmentation(std::string gpsData) {
  return split(gpsData, '$');
}

shared_ptr<GpsInfo> GpsProtocolParsingProcess::GNGGAProcess(
    vector<std::string> gpsData) {

  shared_ptr<GpsInfo> gps_info(new GpsInfo());
  gps_info->Altitude = atof(gpsData[9].c_str());
  gps_info->Latitude = atof(gpsData[2].c_str());
  gps_info->Longitude = atof(gpsData[4].c_str());
  logger->debug("Altitude {}", gps_info->Altitude);
  logger->debug("Latitude {}", gps_info->Latitude);
  logger->debug("Longitude {}", gps_info->Longitude);

  return gps_info;
}
shared_ptr<GpsInfo> GpsProtocolParsingProcess::GPGGAProcess(
    vector<std::string> gpsData) {
  shared_ptr<GpsInfo> gps_info(new GpsInfo());
  gps_info->Altitude = atof(gpsData[9].c_str());
  gps_info->Latitude = atof(gpsData[2].c_str());
  gps_info->Longitude = atof(gpsData[4].c_str());
  logger->debug("Altitude {}", gps_info->Altitude);
  logger->debug("Latitude {}", gps_info->Latitude);
  logger->debug("Longitude {}", gps_info->Longitude);

  return gps_info;
}