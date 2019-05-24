
#include "zwtimecpp/core/test/test_utils/tester_manager.hpp"
#include "zwtimecpp/core/core.hpp"
namespace {
using namespace std;
using namespace zwsd;
using namespace backward;
using namespace core;

class ExceptionHandlerImpl : public ExceptionHandler {
	void onExceptionSync(std::shared_ptr<zwsd::core::BaseException> expec) override {
		SimpleLogger::info("Catch exception %s", expec->toString().c_str());
	}
};

class TestException : public TestElement {
  public:
	TestException() {}
  public:

	void run(int argc, const char **argv) override {
		//测试注册异常回调
		Core::initialize();
//		Core::Instance()->getExceptionHandleCenter().regExceptionHandler(std::make_shared<ExceptionHandlerImpl>());
//		Core::Instance()->getExceptionHandleCenter().regExceptionTransformer([](const std::exception &ec) {
//		  return std::make_shared<BaseException>("TestException: transformerException");
//		});
//		Core::Instance()->getExceptionHandleCenter().postException(std::make_shared<BaseException>("TestException"));
//		Core::Instance()->getExceptionHandleCenter().postException(Core::Instance()->getExceptionHandleCenter().transformException(
//			std::exception()));
	}
	void run() override {
	}

};

ENABLE_TEST(TestException);
}