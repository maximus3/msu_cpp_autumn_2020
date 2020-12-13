#include "binsort.h"

void binfile_sort(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream fin(input_filename, std::ios::in | std::ios::binary);

    size_t files_count = 0;
    std::mutex mutex;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < THREADS_COUNT; i++) {
        threads.push_back(std::thread(thread_sort, std::ref(fin), std::ref(files_count), std::ref(mutex)));
    }
    for (size_t i = 0; i < THREADS_COUNT; i++) {
        threads[i].join();
    }

    std::ofstream fout(output_filename, std::ios::out | std::ios::binary);
    merge_files(fout, files_count);
}

void thread_sort(std::ifstream &fin, size_t &files_count, std::mutex&mutex) {
    uint64_t *buffer = new uint64_t[TMPFILE_MAXCOUNT];

    while (true) {
        size_t buffer_size = 0;
        std::stringstream tmp_file;

        {
            std::unique_lock <std::mutex> Lock(mutex);
            fin.read((char *) buffer, sizeof(uint64_t) * TMPFILE_MAXCOUNT);
            buffer_size = fin.gcount() / sizeof(uint64_t);
    
            if (buffer_size == 0) {
                break;
            }

            tmp_file << "tmpfile" << files_count;
            files_count++;
        }

        std::sort(buffer, buffer + buffer_size);

        std::ofstream fout(tmp_file.str(), std::ios::out | std::ios::binary);

        fout.write((char *) buffer, sizeof(uint64_t) * buffer_size);
    }

    delete []buffer;
}

void merge_files(std::ofstream &fout, size_t &files_count) {
    std::vector<std::ifstream> fins;
    std::priority_queue <std::pair<uint64_t, size_t>, std::vector<std::pair<uint64_t, size_t>>, std::greater <std::pair<uint64_t, size_t>>> queue;

    for (size_t i = 0; i < files_count; i++) {
        std::stringstream tmp_file;
        tmp_file << "tmpfile" << i;
        fins.push_back(std::ifstream(tmp_file.str(), std::ios::in | std::ios::binary));
    }

    for (size_t i = 0; i < files_count; i++) {
        uint64_t digit;
        if (fins[i].read((char *) &digit, sizeof(uint64_t))) {
            queue.push(std::make_pair(digit, i));
        }
    }

    while (!queue.empty()) {
        auto [digit, i] = queue.top();
        queue.pop();

        fout.write((char *) &digit, sizeof(uint64_t));

        if (fins[i].read((char *) &digit, sizeof(uint64_t))) {
            queue.push(std::make_pair(digit, i));
        }
    }

    for (size_t i = 0; i < files_count; i++) {
        std::stringstream tmp_file;
        tmp_file << "tmpfile" << i;
        std::remove(tmp_file.str().c_str());
    }
}