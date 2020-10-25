#include <sstream>

#include "test_runner.h"
#include "matrix.h"

void
unittests(void) {
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    Assert(m.getRows() == rows, "Rows");
    Assert(m.getColumns() == cols, "Columns");

    m[1][2] = 5; // строка 1, колонка 2
    double x = m[4][1];
    Assert(x < 0.0001, "x");

    try {
        std::cout << m[rows][0];
        Assert(0 == 1, "Rows RT");
    } catch (std::out_of_range&) {
        Assert(0 == 0, "Rows RT OK");
    }

    try {
        std::cout << m[0][cols];
        Assert(0 == 1, "Cols RT");
    } catch (std::out_of_range&) {
        Assert(0 == 0, "Cols RT OK");
    }

    try {
        std::cout << m[rows][cols];
        Assert(0 == 1, "Rows Cols RT");
    } catch (std::out_of_range&) {
        Assert(0 == 0, "Rows Cols RT OK");
    }

    m *= 3; // умножение на число

    Assert(m[1][2] == 15, "*=");
    Assert(m[4][1] == 0, "*= (0)");

    Matrix m1(rows, cols);
    Assert (!(m1 == m), "Eq");
    Assert (m1 != m, "NotEq");
    m1[0][0] = 243;
    m1[1][2] = 20;
    
    Matrix m2 = m1 + m;

    Assert(m2[1][2] == 35, "+ (15 + 20)");
    Assert(m2[0][0] == 243, "+ (0 + 243)");
    Assert(m2[4][1] == 0, "+ (0 + 0");
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(unittests, "unittests");
    
    std::cout << "All tests passes successfully!\n";
    return 0;
}
