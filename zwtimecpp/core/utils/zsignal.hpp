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
#include "zwtimecpp/core/jobs/work_queue.hpp"
#include "zwtimecpp/core/utils/nod/nod.hpp"
namespace zwsd {
using namespace std;

#define ENABLE_SIGNAL_LISTENER(ClassName) \
  list<nod::scoped_connection> __zsignalConnections;

#if 1
/**
 * @brief SignalType (last value, cur value)
 *
 */
#define LISTEN_TO(signal, type, do_what)                         \
  {                                                              \
    nod::scoped_connection connection = signal.connect(          \
        [this](const type& last, const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));            \
  }

/**
 * @brief SignalType(void)
 *
 */
#define LISTEN_TO1(signal, type, do_what)                                      \
  {                                                                            \
    nod::scoped_connection connection = signal.connect([this]() { do_what; }); \
    __zsignalConnections.push_back(move(connection));                          \
  }

/**
 * @brief SignalType(const Type curValue)
 *
 */
#define LISTEN_TO2(signal, type, do_what)                     \
  {                                                           \
    nod::scoped_connection connection =                       \
        signal.connect([this](const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));         \
  }
#else
/**
 * @brief SignalType (last value, cur value)
 *
 */
#define LISTEN_TO(signal, type, do_what)                         \
  {                                                              \
    nod::scoped_connection connection = signal.connect(          \
        [this](const type& last, const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));            \
  }

/**
 * @brief SignalType(void)
 *
 */
#define LISTEN_TO1(signal, type, do_what)                                      \
  {                                                                            \
    nod::scoped_connection connection = signal.connect([this]() { do_what; }); \
    __zsignalConnections.push_back(move(connection));                          \
  }

/**
 * @brief SignalType(const Type curValue)
 *
 */
#define LISTEN_TO2(signal, type, do_what)                     \
  {                                                           \
    nod::scoped_connection connection =                       \
        signal.connect([this](const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));         \
  }
#endif
/**
 * @Warning:使用这个宏的时候注意参数是以拷贝的形式传递进去的，局部变量并不会在运算中修改
 */
#define LISTEN_TO_SCOPED(id, signal, type, do_what)           \
  nod::scoped_connection __connection_##id =                  \
      signal.connect([=](const type& last, const type& now) { \
        do_what;                                              \
                                                              \
      });

}  // namespace zwsd