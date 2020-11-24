#pragma once

#include <sstream>
#include <exception>
#include <string>
#include <iostream>

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint="");

void Assert(bool b, const std::string& hint="");

class TestRunner {
private:
  int fail_count = 0;
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name)  {
    try {
	  func();
	  std::cerr << test_name << " OK" << std::endl;
	} catch (std::runtime_error& e) {
	  ++fail_count;
	  std::cerr << test_name << " fail: " << e.what() << std::endl;
	}
}

  ~TestRunner();
};
    
