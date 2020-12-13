#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <utility>
#include <iostream>

constexpr size_t TMPFILE_MAXCOUNT = 128 * 1024;
constexpr size_t THREADS_COUNT = 2;

void binfile_sort(const std::string& input_filename, const std::string& output_filename);

void thread_sort(std::ifstream &fin, size_t &files_count, std::mutex&mutex);

void merge_files(std::ofstream &fout, size_t &files_count);