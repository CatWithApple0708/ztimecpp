#pragma once
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
#include "zwtimecpp/core/utils/cutils/enum_helper.h"

#define MobileWrappingLocationList(marco)                      /**/ \
  marco(kCamera, 0)                                            /**/ \
      marco(kRadar, 1)                                         /**/ \
      marco(kLight, 2)                                         /**/ \
      marco(kSpeaker, 3)                                       /**/ \
      marco(kUltrasonicSensorA, 4)                             /**/ \
      marco(kUltrasonicSensorB, 5)                             /**/ \
      marco(kChassisMotor, 6)                                  /**/ \
      marco(kChassisMotorEncoder, 7)                           /**/ \
      marco(kChassisCoprocessor, 8)                            /**/ \
      marco(kfilmCarriageLifterMotor, 9)                       /**/ \
      marco(kfilmCarriageLifterMotorEncoder, 10)               /**/ \
      marco(kfilmCarriageLifterCoprocessor, 11)                /**/ \
      marco(kfilmCarriageControllorForceMotor, 12)             /**/ \
      marco(kfilmCarriageControllorForceMotorEncoder, 13)      /**/ \
      marco(kfilmCarriageControllorPrestretchMotor, 14)        /**/ \
      marco(kfilmCarriageControllorPrestretchMotorEncoder, 15) /**/ \
      marco(kfilmCarriageControllorForceSensor, 16)            /**/ \
      marco(kfilmCarriageControllorCoprocessor, 17)            /**/

/**
 * @brief 定义枚举
 *
 */
ENUM_HELPER_DEFINE_ENUM(MobileWrappingLocation_t, MobileWrappingLocationList);
/**
 * @brief 使能枚举转换成字符串方法
 *
 */
// ENUM_HELPER_ENABLE_ENUM_TO_STR(mobileWrappingLocationToStr,
//                                MobileWrappingLocation_t,
//                                MobileWrappingLocationList);
