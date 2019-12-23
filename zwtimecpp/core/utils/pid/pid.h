#pragma once
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
typedef struct {
  double kp;
  double ki;
  double kd;

  double current;
  double e0;
  double e1;  //上一次误差
  double e2;  //本次误差

} pid_inc_t;

static INLINE double pid_inc_process(pid_inc_t* handle, double target,
                                     double actual) {
  double ret = 0;
  handle->e0 = target - actual;
  double kpvalue = handle->kp * (handle->e0 - handle->e1);
  double kivalue = handle->ki * handle->e0;
  double kdvalue = handle->kd * (handle->e0 - 2 * handle->e1 + handle->e2);
  return (kpvalue + kivalue + kdvalue);
}

static INLINE void pid