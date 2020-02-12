/*
 * File: work_queue.hpp
 * Project: worker_queue
 * File Created: Thursday, 18th October 2018 5:23:19 pm
 * Author: zhaohe (1013909206@qq.com)
 * -----
 * Last Modified: Thursday, 18th October 2018 5:23:25 pm
 * Modified By: zhaohe (1013909206@qq.com>)
 * -----
 * Copyright 2017 - 2018 zwsd, zwsd
 */
#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include "zwtimecpp/core/thread/thread.hpp"
#include "zwtimecpp/core/utils/concurrentqueue/blockingconcurrentqueue.h"

namespace zwsd {
namespace core {
using namespace std;
/**
 * @brief 保证所有调用均在这个线程中发生
 */
class SyncThread {
  ENABLE_LOGGER(SyncThread);
  bool is_running_ = false;
  string name;
  unique_ptr<Thread> thread_;
  moodycamel::BlockingConcurrentQueue<function<void(void)>> queue_;

 public:
  SyncThread(string name) {
    // logger = zwsd::core::SpdLoggerFactory::Instance().createLogger(name);
    is_running_ = true;
    this->name = name;
    thread_.reset(new Thread(name, [this]() {
      while (1) {
        if (!is_running_) {
          break;
        }
        function<void(void)> call_;
        queue_.wait_dequeue(call_);
        if (call_) call_();
      }
    }));
  };
  void clear() {
    function<void(void)> call_;
    while (queue_.try_dequeue(call_)) {
      /*clear queue*/
    }
  };
  size_t getSize() { return queue_.size_approx(); }
  /**
   * @brief 异步调用
   * @param func
   */
  void asyncCall(function<void(void)> func) {
    ThisThread thisThread;
    if (thread_->getId() == thisThread.getId()) {
      func();
    } else {
      queue_.enqueue(func);
    }
  }

  template <class type>
  type syncCall(function<type(void)> func, type defaultValue) {
    ThisThread thisThread;
    if (thread_->getId() == thisThread.getId()) {
      return func();
    } else {
      type ret = defaultValue;
      atomic_bool seted = {false};
      queue_.enqueue([&]() {
        ret = func();
        seted = true;
        thisThread.wake();
      });
      thisThread.sleep();
      if (!seted) {
        logger->error("{} syncCall fail", name);
      }
      return ret;
    }
  }

  bool onThisThread() {
    ThisThread thisThread;
    return thread_->getId() == thisThread.getId();
  }

  bool syncCallBool(function<bool(void)> func) { return syncCall(func, false); }
  void syncCallVoid(function<void(void)> func) {
    ThisThread thisThread;
    if (thread_->getId() == thisThread.getId()) {
      return func();
    } else {
      atomic_bool seted = {false};
      queue_.enqueue([&]() {
        func();
        seted = true;
        thisThread.wake();
      });
      thisThread.sleep();
      if (!seted) {
        logger->error("{} syncCall fail", name);
      }
      return;
    }
  }

  ~SyncThread() {
    is_running_ = false;
    queue_.enqueue(nullptr);
    if (thread_) thread_->join();
  }

 private:
};
}  // namespace core

}  // namespace zwsd
