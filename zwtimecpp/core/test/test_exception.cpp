
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
		SimpleLogger::info("Catch exception %s", expec.what());
	}
};

class TestException : public TestElement {
  public:
	TestException() {}
  public:

	void run(int argc, const char **argv) override {
		//测试注册异常回调
		Core::initialize();
		shared_ptr<ExceptionHandlerImpl> exceptionHandler = std::make_shared<ExceptionHandlerImpl>();
		Core::Instance()->getExceptionHandleCenter().regExceptionHandler(exceptionHandler);
		BaseException baseException("TestException");
		Core::Instance()->getExceptionHandleCenter().postException(baseException);
	}
	void run() override {
	}
};

ENABLE_TEST(TestException);
}