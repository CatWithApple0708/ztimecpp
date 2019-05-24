//
// Created by zhaohe on 19-5-21.
//

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include "zwtimecpp/core/core.hpp"
#include "zwtimecpp/core/test/test_utils/tester_manager.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

int main(int argc, char const *argv[])
{
//    TestBackWard::run();


	if (argc <= 1){
		SimpleLogger::info("%s ClassName",argv[0]);
		return 0;
	}
	SimpleLogger::info("Run test %s---------------------->",argv[1]);
	TesterManager::Instance().run(argv[1],argc,argv);
    return 0;
}
