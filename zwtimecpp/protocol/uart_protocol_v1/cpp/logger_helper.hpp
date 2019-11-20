//
// Created by zhaohe on 19-10-16.
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
#include "zwtimecpp/core/logger/logger.hpp"
extern "C" {
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_v1.h"
}
#include "uart_protocol_v1_packet.hpp"

namespace zwsd {
using namespace std;
using namespace core;
class UartProtocolV1LoggerHelper {
 public:
  void dump(logger_t logger, level::level_enum level,
            UP_packet_container_t *container);
  void dump(logger_t logger, level::level_enum level,
            shared_ptr<UartProtocolV1Packet> container);
};
}

// logger heler

#define CASE_AND_RET(value) \
  case value:               \
    return os << #value;

template <typename OStream>
static inline OStream &operator<<(OStream &os, PacketType_t packetType) {
  switch (packetType) {
    CASE_AND_RET(kUnkownPacketType)
    CASE_AND_RET(kReceiptPacket)
    CASE_AND_RET(kShakeHandPacket)
    CASE_AND_RET(kPingPacket)
    CASE_AND_RET(kHardwareOperatePacket)
    CASE_AND_RET(kSystemEventReportPacket)
    default:
      break;
  }
  return os << "unkownCode:" << (int)packetType;
}

template <typename OStream>
static inline OStream &operator<<(OStream &os, UP_error_code_t errorCode) {
  switch (errorCode) {
    CASE_AND_RET(kErrorCode_Success)
    CASE_AND_RET(kErrorCode_packetIsTooLong)
    CASE_AND_RET(kErrorCode_receivePacketOverflow)
    CASE_AND_RET(kErrorCode_moduleNotSupport)
    CASE_AND_RET(kErrorCode_DataPointNotSupport)
    CASE_AND_RET(kErrorCode_OperationNotSupport)
    CASE_AND_RET(kErrorCode_NotSupportPacketType)
    CASE_AND_RET(kErrorCode_parsePacketFail)
    CASE_AND_RET(kErrorCode_packetFormatError)
    CASE_AND_RET(kErrorCode_moduleNumNotSupport)
    CASE_AND_RET(kErrorCode_powerIsInActive)
    default:
      break;
  }
  return os << "unkownCode:" << (int)errorCode;
}

template <typename OStream>
static inline OStream &operator<<(OStream &os, UP_operate_code_t operateCode) {
  switch (operateCode) {
    CASE_AND_RET(kOperateCode_read)
    CASE_AND_RET(kOperateCode_write)
    CASE_AND_RET(kOperateCode_report)
    CASE_AND_RET(kOperateCode_openInitiativeReport)
    CASE_AND_RET(kOperateCode_openPeriodReport)
    CASE_AND_RET(kOperateCode_setReportPeriod)
    CASE_AND_RET(kOperateCode_reportRequest)
    default:
      break;
  }
  return os << "unkownCode:" << (int)operateCode;
}

template <typename OStream>
static inline OStream &operator<<(OStream &os,
                                  UP_module_type_code_t moduleType) {
  switch (moduleType) {
    CASE_AND_RET(MTC_NotSet)
    CASE_AND_RET(MTC_HumanSensor)
    CASE_AND_RET(MTC_IndicatorLight)
    CASE_AND_RET(MTC_Light)
    CASE_AND_RET(MTC_Key)
    CASE_AND_RET(MTC_UltrasonicSensor)
    CASE_AND_RET(MTC_LightSensor)
    CASE_AND_RET(MTC_Gps)
    CASE_AND_RET(MTC_CardReader)
    CASE_AND_RET(MTC_HandProtection)
    CASE_AND_RET(MTC_OverflowDetector)
    CASE_AND_RET(MTC_GarbageDumpingWindowsMotor)
    CASE_AND_RET(MTC_GarbageDoorMotor)
    CASE_AND_RET(MTC_Weighting)
    CASE_AND_RET(MTC_Uart)
    default:
      break;
  }
  return os << "unkownCode:" << (int)moduleType;
}

#undef CASE_AND_RET
