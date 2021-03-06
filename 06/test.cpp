#include <sstream>
#include <algorithm>

#include "test_runner.h"
#include "format.hpp"

void
unittests() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    Assert(text == "one+one = 2", "Test 0");
    Assert(format(text) == text, "Format text");

    Assert(format("Nothing to format") == "Nothing to format", "Nothing to format");

    Assert(format("Hi, I am {0}", "1") == "Hi, I am 1", "String");
    Assert(format("ab{0}{1}", 'c', "d") == "abcd", "Char and string");
    
    try {
        format("{0}");
        Assert(1 == 0, "out_of_range 0");
    } catch (const format_out_of_range_error&) {}

    try {
        format("{1}", 1);
        Assert(1 == 0, "out_of_range 1");
    } catch (const format_out_of_range_error&) {}

    try {
        format("{f}", 1);
        Assert(1 == 0, "invalid_argument");
    } catch (const format_invalid_argument_error&) {}

    try {
        format("Hi, {0} {", "Ivan");
        Assert(1 == 0, "runtime_error {");
    } catch (const format_syntax_error&) {}

    try {
        format("Hi, {0}}", "Ivan");
        Assert(1 == 0, "runtime_error }");
    } catch (const format_syntax_error&) {}
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(unittests, "unittests");
    return 0;
}
