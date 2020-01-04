#pragma once
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
#include "zwtimecpp/core/utils/cutils/enum_helper.h"

typedef enum {
  kMWL_notSet = 0,
  kMWL_Camera,
  kMWL_Radar,
  kMWL_Light,
  kMWL_Speaker,
  kMWL_UltrasonicSensorA,
  kMWL_UltrasonicSensorB,
  kMWL_ChassisMotor,
  kMWL_ChassisMotorEncoder,
  kMWL_ChassisCoprocessor,
  kMWL_filmCarriageLifterMotor,
  kMWL_filmCarriageLifterMotorEncoder,
  kMWL_filmCarriageLifterCoprocessor,
  kMWL_filmCarriageControllorForceMotor,
  kMWL_filmCarriageControllorForceMotorEncoder,
  kMWL_filmCarriageControllorPrestretchMotor,
  kMWL_filmCarriageControllorPrestretchMotorEncoder,
  kMWL_filmCarriageControllorForceSensor,
  kMWL_filmCarriageControllorCoprocessor,

} MobileWrappingLocation_t;

static INLINE const char* MobileWrappingLocationToString(MobileWrappingLocation_t val) {
  BEGIN_ENUM_CASE();
  ENUM_CASE_AND_RET2(kMWL, notSet);
  ENUM_CASE_AND_RET2(kMWL, Camera);
  ENUM_CASE_AND_RET2(kMWL, Radar);
  ENUM_CASE_AND_RET2(kMWL, Light);
  ENUM_CASE_AND_RET2(kMWL, Speaker);
  ENUM_CASE_AND_RET2(kMWL, UltrasonicSensorA);
  ENUM_CASE_AND_RET2(kMWL, UltrasonicSensorB);
  ENUM_CASE_AND_RET2(kMWL, ChassisMotor);
  ENUM_CASE_AND_RET2(kMWL, ChassisMotorEncoder);
  ENUM_CASE_AND_RET2(kMWL, ChassisCoprocessor);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageLifterMotor);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageLifterMotorEncoder);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageLifterCoprocessor);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageControllorForceMotor);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageControllorForceMotorEncoder);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageControllorPrestretchMotor);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageControllorPrestretchMotorEncoder);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageControllorForceSensor);
  ENUM_CASE_AND_RET2(kMWL, filmCarriageControllorCoprocessor);
  END_ENUM_CASE();
}

typedef enum {
  kMWSV_notSet = 0,
  kMWSV_bumperSwitch = 1,
  kMWSV_flimBottomLimterSwitch = 2,  //模架底部限位器
  kMWSV_flimTopLimterSwitch = 3,     //模架顶部限位器
  kMWSV_flimLimterSwitch = 4,        //模架上的限位器
  kMWSV_bootUpSwitch = 5,        //模架上的限位器
  kMWSV_startSwitch = 6,        //模架上的限位器
  kMWSV_resetSwitch = 7,        //模架上的限位器
  kMWSV_emergencyStopSwitch = 8,        //模架上的限位器
  //定义系统所需要的按键事件
} MobileWrappingSwitchValue_t;
