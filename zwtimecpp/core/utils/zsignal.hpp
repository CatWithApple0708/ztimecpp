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

#define LISTEN_TO(signal, type, do_what)                         \
  {                                                              \
    nod::scoped_connection connection = signal.connect(          \
        [this](const type& last, const type& now) { do_what; }); \
    __zsignalConnections.push_back(move(connection));            \
  }

}  // namespace zwsd