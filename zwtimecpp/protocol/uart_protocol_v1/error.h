#pragma once
#include "zwtimecpp/core/utils/cutils/enum_helper.h"

typedef enum {
  kNoError = 0,
  //通用异常
  kMotorOvervoltage = 1,  //电机过压
  kMotorOvercurrent,      //电机过流
  kMotorOverhearting,     //电机过热
  kSensorException,  //传感器异常,例如不能读到正确的传感器信息
  kLostConnection,   //通信异常

  //缠绕车异常
  kMachinesMeetsObstacle = 0x1000
} HardwareErrorCode_t;

static INLINE const char* HardwareErrorCodeToString(HardwareErrorCode_t val) {
  BEGIN_ENUM_CASE();
  ENUM_CASE_AND_RET(kNoError);
  ENUM_CASE_AND_RET(kMotorOvervoltage);
  ENUM_CASE_AND_RET(kMotorOvercurrent);
  ENUM_CASE_AND_RET(kMotorOverhearting);
  ENUM_CASE_AND_RET(kSensorException);
  ENUM_CASE_AND_RET(kLostConnection);
  ENUM_CASE_AND_RET(kMachinesMeetsObstacle);
  END_ENUM_CASE();
}
