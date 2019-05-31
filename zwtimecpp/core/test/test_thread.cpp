
#include "zwtimecpp/core/test/test_utils/tester_manager.hpp"
#include "zwtimecpp/core/core.hpp"
namespace {
using namespace std;
using namespace zwsd;
using namespace backward;
using namespace core;

class ExceptionHandlerImpl : public ExceptionHandler {
  public:
	void onExceptionSync(const std::exception &expec) override {
		std::cout << expec.what();
	}
};

class ExceptionHandlerImpl2 : public ExceptionHandler {
  public:
	void onExceptionSync(const std::exception &expec) override {
	}
};

class TestThread : public TestElement, public enable_shared_from_this<TestThread> {
  public:
	TestThread() {}
  public:
	void run(int argc, const char **argv) override {
		//测试注册异常回调
		Core::initialize();

#if 1
		//处理异常会在上面 onExceptionSync中打印
		shared_ptr<ExceptionHandler> exceptionHandler = std::make_shared<ExceptionHandlerImpl>();
		CoreSystemState::Instance().setDefaultExceptionHandler(exceptionHandler);
		//线程运行测试
		Thread thread("TestThread", [this]() {
			SimpleLogger::info("TestThread run.......");
			throw BaseException("TestThread throw baseException");
		});
#endif
#if 0
		//处理异常会在上面 onExceptionSync被回调,但如果没有调用exception->toString, 会自动将exception会自动调用toString
		shared_ptr<ExceptionHandler> exceptionHandler = std::make_shared<ExceptionHandlerImpl2>();
		CoreSystemState::Instance().setDefaultExceptionHandler(exceptionHandler);
		//线程运行测试
		Thread thread("TestThread", [this]() {
		  SimpleLogger::info("TestThread run.......");
		  throw BaseException("TestThread throw baseException");
		});
#endif

#if 0
		//如果没有注册异常处理方法,异常会被抛出,程序会被中止
		Thread thread("TestThread", [this]() {
		  SimpleLogger::info("TestThread run.......");
		  throw BaseException("TestThread throw baseException");
		});

		while (1) {
			sleep(1);
		}
#endif
	}
	void run() override {
	}

};

ENABLE_TEST(TestThread);
}