#include <sstream>

#include "test_runner.h"
#include "serializer.tpp"

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

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(test_1, "test_1");
    runner.RunTest(test_2, "test_2");
    runner.RunTest(test_3, "test_3");
    return 0;
}
