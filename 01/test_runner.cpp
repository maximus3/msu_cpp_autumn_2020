#include "test_runner.h"

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
  if (t != u) {
    std::ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw std::runtime_error(os.str());
  }
}

void Assert(bool b, const std::string& hint) {
  AssertEqual(b, true, hint);
}

/*template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string& test_name) {
    try {
	  func();
	  std::cerr << test_name << " OK" << std::endl;
	} catch (std::runtime_error& e) {
	  ++fail_count;
	  std::cerr << test_name << " fail: " << e.what() << std::endl;
	}
}*/

TestRunner::~TestRunner() {
    if (fail_count > 0) {
      std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
      exit(1);
    }
}
