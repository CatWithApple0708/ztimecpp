#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/utils/run_when_exit.hpp"
namespace zwsd {
using namespace std;
/**
 * @Usage
 *
 * std::recursive_mutex lock_;
 *
 * function(){
 *  TRY_LOCK_RECURSIVE_MUTEX(lock_)
 * by another thread");
 * }
 *
 */
#define TRY_LOCK_RECURSIVE_MUTEX(lockName)                                     \
  bool __FUNCTION__##__LINE__##lock = false;                                   \
  if (!lockName.try_lock()) {                                                  \
    logger->error("call {} fail,due to function is in locking", __FUNCTION__); \
    return;                                                                    \
  }                                                                            \
  __FUNCTION__##__LINE__##lock = true;                                         \
  RUN_WHEN_EXIT(if (__FUNCTION__##__LINE__##lock) lockName.unlock());

}  // namespace zwsd