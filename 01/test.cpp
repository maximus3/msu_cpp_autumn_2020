#include "test_runner.h"
#include "myalloc.h"

void
unittests() {
    Allocator alloc = Allocator();
    
    Assert(alloc.alloc(1) == nullptr, "");
    alloc.reset();
    
    alloc.makeAllocator(100);
    Assert(alloc.alloc(1) != nullptr, "alloc 1");
    Assert(alloc.alloc(10) != nullptr, "alloc 10");
    Assert(alloc.alloc(90) == nullptr, "alloc > (90)");
    Assert(alloc.alloc(89) != nullptr, "alloc 89");
    Assert(alloc.alloc(1) == nullptr, "alloc > (1)");
    
    alloc.reset();
    alloc.makeAllocator(100);
    Assert(alloc.alloc(1000) == nullptr, "alloc > (1000)");
    Assert(alloc.alloc(101) == nullptr, "alloc > (101)");
    Assert(alloc.alloc(100) != nullptr, "alloc 100");
    Assert(alloc.alloc(101) == nullptr, "alloc > (101)");
    Assert(alloc.alloc(1) == nullptr, "alloc > (1)");
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(unittests, "Unittests");
    return 0;
}
