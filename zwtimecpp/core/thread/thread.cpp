//
// Created by zhaohe on 19-5-21.
//

#include "thread.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

Thread::Thread(std::function<void()> run) {
	workThread.reset(new thread([this](){
	  work();
	}));
}
void Thread::sleep() {

}
void Thread::sleepForMs(int ms) {

}
void Thread::yield() {

}
void Thread::work() {

}