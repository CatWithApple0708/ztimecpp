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
class WorkQueue {
  bool is_running_ = false;
  unique_ptr<Thread> thread_;
  moodycamel::BlockingConcurrentQueue<function<void(void)>> queue_;

 public:
  WorkQueue(string name) {
    is_running_ = true;
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
  void Clear() {
    function<void(void)> call_;
    while (queue_.try_dequeue(call_)) {
      /*clear queue*/
    }
  };
  size_t getSize() { return queue_.size_approx(); }
  void EnQueue(function<void(void)> func) { queue_.enqueue(func); }
  ~WorkQueue() {
    is_running_ = false;
    queue_.enqueue(nullptr);
    if (thread_) thread_->join();
  }

 private:
};
}  // namespace core

}  // namespace zwsd
