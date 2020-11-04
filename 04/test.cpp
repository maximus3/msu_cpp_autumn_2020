#include <sstream>

#include "test_runner.h"
#include "bigint.h"

void
unittests(void) {
    BigInt a = 1;

    Assert (a * BigInt() == BigInt("0"), "a * 0");

    Assert(a == BigInt(1), "a == BI(1)");
    Assert(a == BigInt("1"), "a == BI(1) str");

    BigInt b("123456789012345678901234567890");

    Assert(a + 1 == BigInt(2), "a + 1");
    Assert(a + b == BigInt("123456789012345678901234567891"), "a + b");
    Assert(1 + b == BigInt("123456789012345678901234567891"), "1 + b");

    BigInt a1 = -1;
    Assert(a1 == BigInt(-1), "a1 == BI(-1)");
    Assert(a1 == BigInt("-1"), "a1 == BI(-1) str");

    Assert(a1 + 1 == BigInt(0), "a1 + 1");
    Assert(a1 + b == BigInt("123456789012345678901234567889"), "a1 + b");
    Assert(1 + a1 == BigInt("0"), "1 + a1");

    BigInt c = a * b + 2;
    BigInt c1(b * a + 2);

    Assert (c == BigInt("123456789012345678901234567892"), "c == ");
    Assert (c1 == BigInt("123456789012345678901234567892"), "c1 == ");
    
    BigInt d;
    d = std::move(c);
    a = d + b;
    
    Assert (a == BigInt("246913578024691357802469135782"), "a == d + b");

    a = BigInt("43245");
    b = BigInt("-923492949233");
    c = BigInt("-39936452589581085");
    d = BigInt("-923492905988");
    Assert (a * b == c, "BIG a * b");
    Assert (a + b == BigInt("-923492905988"), "BIG a + b");
    Assert (b + a == d, "BIG b + a");
    
    Assert (-a * -b == c, "BIG -a * -b");
    Assert (-a + -b == -d, "BIG -a + -b");
    Assert (-b + -a == -d, "BIG -b + -a");

    Assert (BigInt("-4324234") + BigInt("-95349") == BigInt("-4419583"), "-X + -X");
    Assert (BigInt("-4324234") * BigInt("-95349") == BigInt("412311387666"), "-X * -X");
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(unittests, "unittests");
    return 0;
}
