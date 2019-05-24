#pragma once
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <vector>
namespace zwsd {
namespace core {
using namespace std;
class Singal {
	condition_variable cv_;
	std::mutex mtx_;

  public:
	bool sleep_for_us(int us) {
		if (us < 0)
			return true;
		std::unique_lock<std::mutex> lck(mtx_);
		if (cv_.wait_for(lck, std::chrono::microseconds(us)) == std::cv_status::timeout) {
			return true;
		}
		return false;
	};

	bool sleep(){
		std::unique_lock<std::mutex> lck(mtx_);
		cv_.wait(lck);
		return true;
	}
	void notify() {
		cv_.notify_all();
	}
};
}
} // namespace zwsd