#pragma once
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
typedef struct {
  float kp;
  float ki;
  float kd;

  float current;
  float e0;
  float e1;  //上一次误差
  float e2;  //本次误差

} pid_inc_t;

static INLINE float pid_inc_process(pid_inc_t* handle, float target,
                                     float actual) {
  float ret = 0;
  handle->e0 = target - actual;
  float kpvalue = handle->kp * (handle->e0 - handle->e1);
  float kivalue = handle->ki * handle->e0;
  float kdvalue = handle->kd * (handle->e0 - 2 * handle->e1 + handle->e2);
  return (kpvalue + kivalue + kdvalue);
}

static INLINE void pid