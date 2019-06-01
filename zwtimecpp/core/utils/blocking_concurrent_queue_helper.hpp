//
// Created by zhaohe on 19-6-1.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "zwtimecpp/core/utils/concurrentqueue/blockingconcurrentqueue.h"
namespace zwsd {
namespace core{
using namespace std;
using namespace moodycamel;
template <class T>
static inline void clearQueue(BlockingConcurrentQueue<T>& queue){
  T t;
  while(queue.try_dequeue(t))
  ;
}
}
}


