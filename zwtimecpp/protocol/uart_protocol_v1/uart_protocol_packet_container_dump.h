#pragma once
#include <stdio.h>
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_parse.h"

#define CASE_AND_RET(value) \
  case value:               \
    return #value;

static INLINE char* unkown_code_to_str(const char* describe, int code) {
  static char buf[30] = {0};
  snprintf(buf, ARRARY_SIZE(buf), "%s:%d", describe, code);
  return buf;
}

static INLINE const char* PacketType_to_str(PacketType_t packetType) {
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
  return unkown_code_to_str("unkownPacketType", (int)packetType);
}

static INLINE const char* ErrorCode_to_str(UP_error_code_t errorCode) {
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
  return unkown_code_to_str("unkownErrorCode", (int)errorCode);
}

static INLINE const char* OperateCode_to_str(UP_operate_code_t operateCode) {
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
  return unkown_code_to_str("unkownOperateCode:", (int)operateCode);
}

static INLINE const char* GenernalSystemEvent_to_str(
    UP_GenernalSystemEvent_t genernalSystemEvent) {
  switch (genernalSystemEvent) {
    CASE_AND_RET(kSystemSetup)
    CASE_AND_RET(KSystemWhoAmI)
    default:
      break;
  }
  return unkown_code_to_str("unkownGenernalSystemEvent:",
                            (int)genernalSystemEvent);
}

static INLINE const char* ModuleType_to_str(UP_module_type_code_t moduleType) {
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
    CASE_AND_RET(MTC_GripMotor)
    CASE_AND_RET(MTC_GarbageSensor)
    CASE_AND_RET(MTC_PhotoLight)
    CASE_AND_RET(MTC_DryGarbageUart)
    CASE_AND_RET(MTC_WetGarbageUart)
    CASE_AND_RET(MTC_GarbageConveyerMotor)
    CASE_AND_RET(MTC_PhotoSensor)
    CASE_AND_RET(MTC_GripStepMotor)
    CASE_AND_RET(MTC_RazorStepMotor)
    CASE_AND_RET(MTC_HotMelt)
    CASE_AND_RET(MTC_GarbageBeltSensor)
    CASE_AND_RET(MTC_SealXMotor)
    CASE_AND_RET(MTC_SealYMotor)
    CASE_AND_RET(MTC_TakePhoto)
    CASE_AND_RET(MTC_MobileWrappingMachine)
    default:
      break;
  }
  return unkown_code_to_str("unkownModuleType", (int)moduleType);
}


char** up_packet_container_dump(UP_packet_container_t* container, int* str_size);
char* up_packet_container_dump_in_one_line(UP_packet_container_t* container);