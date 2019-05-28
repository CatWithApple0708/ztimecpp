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
	// weak_ptr<string> value_wakeup;
	// {
	// 	shared_ptr<string> value(new string());
	// 	value_wakeup = value;
	// 	SimpleLogger::info("%p",value_wakeup.lock().get());
	// }
	// SimpleLogger::info("%p",value_wakeup.lock().get());

	SimpleLogger::info("Run test %s---------------------->",argv[1]);
	TesterManager::Instance().run(argv[1],argc,argv);
	Object& a = TesterManager::Instance();





	printf("xxxxx %s\n", typeid(a).name());
	return 0;
}
