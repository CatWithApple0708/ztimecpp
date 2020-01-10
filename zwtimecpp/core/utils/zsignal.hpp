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
#include "zwtimecpp/core/utils/nod/nod.hpp"
namespace zwsd {
using namespace std;

#define ENABLE_SIGNAL_LISTENER() \
  list<nod::scoped_connection> __zsignalConnections;

#define LISTEN_TO(signal, type, do_what)                                     \
  {                                                                          \
    nod::scoped_connection connection =                                      \
        signal.connect([&](const type& last, const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));                        \
  }

#define LISTEN_TO1(signal, type, do_what)                                   \
  {                                                                         \
    nod::scoped_connection connection = signal.connect([&]() { do_what; }); \
    __zsignalConnections.push_back(move(connection));                       \
  }

#define LISTEN_TO2(signal, type, do_what)                  \
  {                                                        \
    nod::scoped_connection connection =                    \
        signal.connect([&](const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));      \
  }

#define LISTEN_TO_SCOPED(id, signal, type, do_what)                        \
  nod::scoped_connection __connection_##id =                               \
      signal.connect([&](const type& last, const type& now) { do_what; }); \

}  // namespace zwsd