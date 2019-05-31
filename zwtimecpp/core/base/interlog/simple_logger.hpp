//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/utils/backward_helper.hpp"
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <vector>

namespace zwsd {
namespace core {
using namespace std;

class SimpleLogger : public Object {
    static bool coreLogEnable;

  public:
    static void log(const char *format, ...) {
        if (!coreLogEnable) {
            return;
        }
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }

    static void trace(const char *format, ...) {
        if (!coreLogEnable) {
            return;
        }
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
    static void info(const char *format, ...) {
        if (!coreLogEnable) {
            return;
        }
        va_list args;
        printf("CoreInfo message: ");
        va_start(args, format);
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }
    static void fatal(const char *format, ...) {
        if (!coreLogEnable) {
            return;
        }
        va_list args;
        va_start(args, format);
        printf("CoreFatal message: ");
        vprintf(format, args);
        printf("\n");
        printf("Cur location: StackInfo: %s", getStackInfo().c_str());
        va_end(args);
        exit(-1);
    }

    static void error(const char *format, ...) {
        if (!coreLogEnable) {
            return;
        }
        va_list args;
        printf("CoreError message: ");
        va_start(args, format);
        vprintf(format, args);
        printf("\n");
        va_end(args);
    }

    static void enableLog() {
        coreLogEnable = true;
    }
};
} // namespace core

} // namespace zwsd
