//
// Created by zhaohe on 19-6-6.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/utils/concurrentqueue/blockingconcurrentqueue.h"
#include "zwtimecpp/core/utils/concurrentqueue/concurrentqueue.h"
namespace zwsd {
namespace core {
using namespace std;
using namespace moodycamel;
class QueueUtils {
 public:
  template <class T>
  static void dumpTo(ConcurrentQueue<shared_ptr<T>>& from,
                     ConcurrentQueue<shared_ptr<T>>& to) {
    shared_ptr<T> t;
    while (from.size_approx() > 0) {
      from.try_dequeue(t);
      to.enqueue(t);
    }
  }

  template <class T>
  static void dumpTo(BlockingConcurrentQueue<shared_ptr<T>>& from,
                     BlockingConcurrentQueue<shared_ptr<T>>& to) {
    shared_ptr<T> t;
    while (from.size_approx() > 0) {
      from.try_dequeue(t);
      to.enqueue(t);
    }
  }

  template <class T>
  static void dumpTo(ConcurrentQueue<unique_ptr<T>>& from,
                     ConcurrentQueue<unique_ptr<T>>& to) {
    unique_ptr<T> t;
    while (1) {
      from.try_dequeue(t);
      if (t)
        to.enqueue(move(t));
      else
        break;
    }
  }

  template <class T>
  static void dumpTo(BlockingConcurrentQueue<unique_ptr<T>>& from,
                     BlockingConcurrentQueue<unique_ptr<T>>& to) {
    unique_ptr<T> t;
    while (1) {
      from.try_dequeue(t);
      if (t)
        to.enqueue(move(t));
      else
        break;
    }
  }

  template <class T>
  static T removeOne(ConcurrentQueue<T>& from) {
    T v;
    from.try_dequeue(v);
    return move(v);
  }

  template <class T>
  static T removeOne(BlockingConcurrentQueue<T>& from) {
    T v;
    from.try_dequeue(v);
    return move(v);
  }

  template <class T>
  static void clear(ConcurrentQueue<T>& from) {
    T v;
    while (from.size_approx() > 0) from.try_dequeue(v);
  }

  template <class T>
  static void clear(BlockingConcurrentQueue<T>& from) {
    T v;
    while (from.size_approx() > 0) from.try_dequeue(v);
  }
};
}  // namespace core

}  // namespace zwsd
