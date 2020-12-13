#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include "test_runner.h"
#include "binsort.h"

void bin_file_gen(const std::string& filename, size_t count) {
    std::ofstream fout(filename, std::ios::out | std::ios::binary);

    std::mt19937_64 generator;

    uint64_t digit;

    for (size_t i = 0; i < count; i++) {
        digit = generator();
        fout.write( (char *) &digit, sizeof(uint64_t));
    }
}

void
unittests() {
    std::string input_filename("in");
    std::string output_filename("out");

    bin_file_gen(input_filename, 9000000);

    binfile_sort(input_filename, output_filename);

    std::ifstream fin(output_filename, std::ios::in | std::ios::binary);

    uint64_t prev = 0, cur;
    while (fin.read((char *) &cur, sizeof(uint64_t))) {
        assert(prev <= cur);
        prev = cur;
    }

    std::remove(input_filename.c_str());
    std::remove(output_filename.c_str());
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(unittests, "unittests");
    return 0;
}
