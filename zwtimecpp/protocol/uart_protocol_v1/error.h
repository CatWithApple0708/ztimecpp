#pragma once
#include "zwtimecpp/core/utils/cutils/enum_helper.h"

#define HardwareErrorCodeList(marco) /**/ \
  marco(kNoError, 0)                 /**/ \
      marco(kMotorOvervoltage, 1)    /**/ \
      marco(kMotorOvercurrent, 2)    /**/ \
      marco(kMotorOverhearting, 3)   /**/ \
      marco(kSensorException, 4)     /**/ \
      marco(kLostConnection, 5)      /**/

/**
 * @brief 定义枚举
 *
 */
ENUM_HELPER_DEFINE_ENUM(HardwareErrorCode_t, HardwareErrorCodeList);
/**
 * @brief 使能枚举转换成字符串方法
 *
 */
ENUM_HELPER_ENABLE_ENUM_TO_STR(hardwareErrorCodeToStr, HardwareErrorCode_t,
                               HardwareErrorCodeList);
