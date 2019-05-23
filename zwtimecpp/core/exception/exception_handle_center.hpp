//
// Created by zhaohe on 19-5-23.
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

namespace zwsd {
using namespace std;

class ExceptionHandleCenter {
  private:
	ExceptionHandleCenter() {}
  public:
	static ExceptionHandleCenter &instance()
	{
	    static ExceptionHandleCenter value;
	    return value;
	}
};
}


