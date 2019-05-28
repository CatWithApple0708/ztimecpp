//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <stdarg.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include "zwtimecpp/core/utils/backward_helper.hpp"
#include "zwtimecpp/core/base/object.hpp"

#define  CORE_LOG_ENABLE
namespace zwsd {
namespace core{
using namespace std;

class SimpleLogger :public Object{
  public:
	static void log(const char* format,...){
#ifdef CORE_LOG_ENABLE
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		printf("\n");
		va_end(args);
#else

#endif
	}

	static void trace(const char* format,...){
#ifdef CORE_LOG_ENABLE
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		printf("\n");
		va_end(args);
#else
#endif
	}
	static void info(const char* format,...){
		va_list args;
		printf("CoreInfo message: ");
		va_start(args, format);
		vprintf(format, args);
		printf("\n");
		va_end(args);
	}
	static void fatal(const char* format,...){
		va_list args;
		va_start(args, format);
		printf("CoreFatal message: ");
		vprintf(format, args);
		printf("\n");
		printf("Cur location: StackInfo: %s",getStackInfo().c_str());
		va_end(args);
		exit(-1);
	}

	static void error(const char* format,...){
		va_list args;
		printf("CoreError message: ");
		va_start(args, format);
		vprintf(format, args);
		printf("\n");
		va_end(args);
	}
};
}

}


