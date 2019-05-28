//
// Created by zhaohe on 19-5-28.
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
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/utils/signal.hpp"
namespace zwsd {
namespace core {
using namespace std;
class ThreadInfo : public Object{
  public:
	string name;
	Singal signal;
};
}
}


