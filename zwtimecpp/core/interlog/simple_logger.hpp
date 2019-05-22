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

namespace zwsd {
using namespace std;

class SimpleLogger {

	static void log(const char* format,...){
// #ifdef CORE_LOG_ENABLE
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		printf("\n");
		va_end(args);
// #else

// #endif
	}
};
}


