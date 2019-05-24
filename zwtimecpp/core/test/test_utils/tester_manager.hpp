//
// Created by zhaohe on 19-5-24.
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
#include "zwtimecpp/core/interlog/simple_logger.hpp"
namespace {
class Initializer {
  public:
	Initializer(std::function<void()> init) {
		init();
	}
};
}
namespace zwsd {
namespace core {
using namespace std;

class TestElement {
  public:
	virtual void run() = 0;
	virtual void run(int argc, char const *argv[]) = 0;
};

class TesterManager {
	map<string, shared_ptr<TestElement>> testElementsMap;
	TesterManager() {};

  public:
	static TesterManager &Instance() {
		static TesterManager value;
		return value;
	}

	template<class T>
	void pushTestElement(string name) {
		shared_ptr<TestElement> value(new T());
		testElementsMap[name] = value;
	}

	void run(string module, int argc, char const *argv[]) {
		if (testElementsMap.find(module) != testElementsMap.end()) {
			testElementsMap[module]->run(argc, argv);
		}
	}
};
}
}
#define ENABLE_TEST(className) static Initializer className##Initializer([]() {	SimpleLogger::info("Push test element:  "#className);	zwsd::core::TesterManager::Instance().pushTestElement<className>(#className);});



