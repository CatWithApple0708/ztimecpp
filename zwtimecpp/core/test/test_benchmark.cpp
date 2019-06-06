
#include "zwtimecpp/core/core.hpp"
#include "zwtimecpp/core/test/test_utils/tester_manager.hpp"
#include "zwtimecpp/core/benchmark/benchmark_factory.hpp"
namespace {
using namespace std;
using namespace zwsd;
using namespace backward;
using namespace core;

class TestBenchMark : public TestElement {
 public:
  TestBenchMark() {}
 public:

  void run(int argc, const char **argv) override {
	//测试注册异常回调
	BenchmarkFactory::initialize(true);
	benchmark_t bm =
		BenchmarkFactory::Instance()->createBenchmark("test_benchmark");
	Benchmark::start(bm);
	sleep(1);
	Benchmark::end(bm);
  }
  void run() override {
  }
};

ENABLE_TEST(TestBenchMark);
}