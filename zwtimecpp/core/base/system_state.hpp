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
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/base/exception_handler.hpp"
#include "zwtimecpp/core/base/thread_info.hpp"

namespace zwsd {
namespace core{
using namespace std;
using namespace core;

class SystemState : public Object
{
	map<pthread_t, shared_ptr<ThreadInfo>> threadInfoMap;

	std::mutex lock_;
	atomic_int ourThreadNum;
	weak_ptr<ExceptionHandler> threadDefaultExceptionHandler;
	SystemState() {
		SimpleLogger::trace("SystemState");
	}

  public:
	static SystemState &Instance() {
		static SystemState value;
		return value;
	}
	/**
	 * @brief Get the Thread Info object,如果是自己创建的线程应该在线程创建的时刻,调用createThreadInfo
	 * 
	 * @param id 
	 * @return shared_ptr<ThreadInfo> 
	 */
	shared_ptr<ThreadInfo> getThreadInfo(pthread_t id)
	{
		std::lock_guard<std::mutex> lock(lock_);
		auto result = threadInfoMap.find(id);
		if (result != threadInfoMap.end())
		{
			return result->second;
		}
		else
		{
//			 shared_ptr<ThreadInfo> threadInfo;
//			 threadInfo.reset(new ThreadInfo());
//			 threadInfoMap[id] = threadInfo;
			return nullptr;
		}
	}

	shared_ptr<ThreadInfo> createThreadInfo(string name)
	{
		shared_ptr<ThreadInfo> threadInfo;
		threadInfo.reset(new ThreadInfo());
		threadInfo->name = name;
		threadInfoMap[pthread_self()] = threadInfo;
		return threadInfo;
	}

	void clearThreadInfo(pthread_t id) {
		{
			std::lock_guard<std::mutex> lock(lock_);
			threadInfoMap.erase(id);
		}
	}

	void setThreadExceptionHandler(shared_ptr<ExceptionHandler> handler){
		threadDefaultExceptionHandler = handler;
	}

	shared_ptr<ExceptionHandler> getThreadExceptionHandler(){
		return threadDefaultExceptionHandler.lock();
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
	virtual ~SystemState() {
		SimpleLogger::trace("SystemState");
	}
private:

	string threadIdToStr(pthread_t id) {
		return to_string(id);
	};
};
}
}


