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
#include <atomic>
#include "zwtimecpp/core/utils/signal.hpp"

namespace zwsd {
namespace core{
using namespace std;
using namespace core;


class ThreadState {
	map<pthread_t, string> threadsNameMap;
	map<pthread_t, shared_ptr<Singal>> signalsMap;

	std::mutex lock_;
	std::mutex lockThreadsNameMap;
	atomic_int ourThreadNum;

	//监听线程,这个线程全局只有一个,且不能使用core::Thread,因为这个线程是用来服务于core::Thread的

	ThreadState() {}

  public:
	static ThreadState &Instance() {
		static ThreadState value;
		return value;
	}


	shared_ptr<Singal> getSignal(pthread_t id) {
		std::lock_guard<std::mutex> lock(lock_);
		auto result = signalsMap.find(id);
		if (result != signalsMap.end()) {
			return result->second;
		} else {
			shared_ptr<Singal> sig;
			sig.reset(new Singal());
			signalsMap[id] = sig;
			return sig;
		}
	}
	void setThreadName(pthread_t id, string name) {
		std::lock_guard<std::mutex> lock(lockThreadsNameMap);
		threadsNameMap[id] = name;
	};

	string getThreadName(pthread_t id) {
		std::lock_guard<std::mutex> lock(lockThreadsNameMap);
		auto result = threadsNameMap.find(id);
		if (result != threadsNameMap.end()) {
			return result->second;
		} else {
			return threadIdToStr(id);
		}
	}
	void clearThreadInfo(pthread_t id) {
		{
			std::lock_guard<std::mutex> lock(lock_);
			signalsMap.erase(id);
		}

		{
			std::lock_guard<std::mutex> lock(lockThreadsNameMap);
			threadsNameMap.erase(id);
		}
	}


	int getOurThreadNum()const {return ourThreadNum.load();}
	int increaseOurThreadNum(){
		ourThreadNum++;
		return ourThreadNum;
	}
	int decreaseOurThreadNum(){
		ourThreadNum--;
		return ourThreadNum;
	}
private:

	string threadIdToStr(pthread_t id) {
		return to_string(id);
	};
};
}
}


