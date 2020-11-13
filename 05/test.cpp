#include <sstream>
#include <algorithm>

#include "test_runner.h"
#include "serializer.hpp"

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

void
test_1() {
    std::stringstream stream;

    Data x { 1, true, 2 };
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    Assert(err == Error::NoError, "Error");
    Assert(x.a == y.a, "a");
    Assert(x.b == y.b, "b");
    Assert(x.c == y.c, "c");
}

void
test_2() {
    std::stringstream stream;

    Data x { 324243, false, 213 };
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 324243, false, 213 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    Assert(err == Error::NoError, "Error");
    Assert(x.a == y.a, "a");
    Assert(x.b == y.b, "b");
    Assert(x.c == y.c, "c");
}

void
test_3() {
    std::stringstream stream;

    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    Assert(err == Error::CorruptedArchive, "Error");
}

void
test_4() {
    std::stringstream stream;

    Data y { 0, false, 0 };
    stream << "-123 true 123";
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    Assert(err == Error::CorruptedArchive, "Error");
}

void
test_5() {
    std::stringstream stream;

    Data y { 0, false, 0 };
    stream << "123 false -1";
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    Assert(err == Error::CorruptedArchive, "Error");
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(test_1, "test_1");
    runner.RunTest(test_2, "test_2");
    runner.RunTest(test_3, "test_3");
    runner.RunTest(test_4, "test_4");
    runner.RunTest(test_5, "test_5");
    return 0;
}
