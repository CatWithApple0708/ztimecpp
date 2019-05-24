
#include "zwtimecpp/core/utils/backward/backward.hpp"
#include "zwtimecpp/core/test/test_utils/tester_manager.hpp"
namespace {
using namespace std;
using namespace zwsd;
using namespace backward;
using namespace core;
class TestBackWard :public TestElement{
  public:

  public:
	void run(int argc, const char **argv) override {
		func1();
	}
	void run() override {
	}
  private:
	static void func1() {
		func2();
	}
	static void func2() {
		func3();
	}
	static void func3() {
  	    printf("func3...1...\n");
		StackTrace st;
		st.load_here(32);
		Printer p;
		p.object = true;
		p.snippet = true;
		p.color_mode = ColorMode::always;
		p.address = true;
		printf("func3...2...\n");
		ostringstream out;
		p.print(st, out);
		printf("%s \n",out.str().c_str());
		printf("func3...3...\n");
	}
};
ENABLE_TEST(TestBackWard);
}