//
// Created by zhaohe on 19-5-21.
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
#include <sstream>
#include "../utils/backward/backward.hpp"
namespace zwsd {
using namespace std;
using namespace backward;

class TestBackWard {

  public:
	static void run() {
		func1();
	}

  private:
	static void func1() {
		func2();
	}
	static void func2() {
		func3();
	}
	static void func3() {
		StackTrace st;
		st.load_here(32);
		Printer p;
		p.object = true;
		p.snippet = true;
		p.color_mode = ColorMode::always;
		p.address = true;

		ostringstream out;
		p.print(st, out);
		printf("%s \n",out.str().c_str());
	}
};
}


