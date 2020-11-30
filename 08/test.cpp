#include <algorithm>
#include <cassert>
#include "test_runner.h"
#include "ThreadPool.hpp"

struct A {};
void foo(const A&) {}

void
unittests() {
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);

    auto task3 = pool.exec([](int x) { return x * 2; }, 1);
    assert(task3.get() == 2);

    int x = 5;
    auto task4 = pool.exec([x](int y) { return x + y * 2; }, 1);
    assert(task4.get() == 7);
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(unittests, "unittests");
    return 0;
}
