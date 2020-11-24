#include <algorithm>
#include <cassert>
#include "test_runner.h"
#include "vector.hpp"


void
test_1() {
    Vector<int> vec;
    assert(vec.size() == 0);

    vec.push_back(1);
    assert(vec[0] == 1);
    assert(vec.size() == 1);

    vec.push_back(5);
    vec.push_back(6);
    assert(vec[0] == 1);
    assert(vec[1] == 5);
    assert(vec[2] == 6);
    assert(vec.size() == 3);

    vec.pop_back();
    assert(vec[0] == 1);
    assert(vec[1] == 5);
    assert(vec.size() == 2);

    vec.emplace_back(4);
    assert(vec[0] == 1);
    assert(vec[1] == 5);
    assert(vec[2] == 4);
    assert(vec.size() == 3);

    vec.emplace_back(1, 2, 3);
    assert(vec[0] == 1);
    assert(vec[1] == 5);
    assert(vec[2] == 4);
    assert(vec[3] == 1);
    assert(vec[4] == 2);
    assert(vec[5] == 3);
    assert(vec.size() == 6);
}

void
test_2() {
    Vector vec(3, 1);

    assert(vec.size() == 3);
    assert(vec[0] == 1);
    assert(vec[1] == 1);
    assert(vec[2] == 1);

    vec.reserve(10);
    assert(vec.size() == 3);
    assert(vec.capacity() == 10);

    vec.resize(4);
    assert(vec.size() == 4);
    assert(vec.capacity() == 10);
    assert(vec[3] == 0);

    vec.resize(2);
    assert(vec.size() == 2);
    assert(vec.capacity() == 10);

    vec.reserve(5);
    assert(vec.size() == 2);
    assert(vec.capacity() == 10);

    vec.resize(100);
    assert(vec.size() == 100);
    assert(vec.capacity() == 100);
    assert(vec[37] == 0);
    assert(vec[43] == 0);
    assert(vec[99] == 0);
}

void
unittests() {
    Vector vec{1, 2, 3};

    assert(vec.size() == 3);
    assert(vec[0] == 1);
    assert(vec[1] == 2);
    assert(vec[2] == 3);

    vec.push_back(10);
    vec.pop_back();
    vec.push_back(100);
    assert(vec.size() == 4);

    auto f = std::find(vec.begin(), vec.end(), 2);
    assert(f - vec.begin() == 1);
    assert(*f == 2);

    auto rf = std::find(vec.rbegin(), vec.rend(), 2);
    assert(*rf == 2);
    assert(rf - vec.rbegin() == 2);

    rf = std::find(vec.rbegin(), vec.rend(), 1);
    assert(*rf == 1);
    assert(rf - vec.rbegin() == 3);

    rf = std::find(vec.rbegin(), vec.rend(), 100);
    assert(*rf == 100);
    assert(rf == vec.rbegin());

    rf = std::find(vec.rbegin(), vec.rend(), 123);
    assert(rf == vec.rend());

    assert(vec[3] == 100);
    assert(!vec.empty());
    vec.clear();
    assert(vec.empty());

    vec.push_back(100);
    assert(vec.size() == 1);
    assert(vec[0] == 100);
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(test_1, "push, pop, emplace");
    runner.RunTest(test_2, "resize, reserve");
    runner.RunTest(unittests, "unittests");
    return 0;
}
