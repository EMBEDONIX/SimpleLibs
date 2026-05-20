//
// Created by Saeid Yazdani on 12/23/2023.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <array>

#include "embedonix/simplelibs/fileio/filereader.h"
#include "embedonix/simplelibs/utilities/benchmark.h"

void sleepFunction(int milli) {
    // Convert seconds to a std::chrono duration
    std::chrono::milliseconds duration(milli);

    // Sleep for the specified duration
    std::this_thread::sleep_for(duration);
}

void read_file_bytes(std::string path) {
    volatile auto content = embedonix::simplelibs::fileio
    ::readers::read_file_bytes(path);
}

void read_file_bytes_caller_alloc(std::string path, std::vector<std::byte> &buffer) {
    volatile auto result = embedonix::simplelibs::fileio::readers::read_file_bytes_into(
            path, buffer);
    (void)result;
}

void read_file(std::string path) {
    volatile auto result = embedonix::simplelibs::fileio::readers::
    read_file(path);
}

void read_file_string(std::string path) {
    volatile auto result = embedonix::simplelibs::fileio::readers::
    read_file_string(path);
}

// List of files
constinit auto files = std::array<std::string_view, 3>{
        "../resources/random-files/one-mb-file",
        "../resources/random-files/two-mb-file",
        "../resources/random-files/ten-mb-file"
};

// Number of runs for each read file function
constinit size_t testsPerFile = 20;

int main() {

    // Allocate a big enough buffer for files up to 10MB
    auto buffer = std::vector<std::byte>(11'000'000);

    std::cout << "Performing average duration of fileio read functions on "
              << files.size() << " files, each file for " << testsPerFile
              << " times" << "\n";

    // Benchmark all functions with three file size, each 10 times
    for (size_t i = 0; i < files.size(); ++i) {
        std::cout << "Benchmarking "
                  << files[i].substr(files[i].find_last_of("/", files[i].size()) + 1)
                  << "\n";

        std::cout << "read_file_bytes_caller_alloc:\t\t" <<
                  embedonix::simplelibs::utilities::benchmark::measure::
                  function_average_execution_time(testsPerFile,
                                                  read_file_bytes_caller_alloc,
                                                  files[i].data(),
                                                  buffer)
                  << "\n";

        std::cout << "read_file_bytes:\t\t\t" <<
                  embedonix::simplelibs::utilities::benchmark::measure::
                  function_average_execution_time(testsPerFile,
                                                  read_file_bytes,
                                                  files[i].data())
                  << "\n";

        std::cout << "read_file:\t\t\t\t" <<
                  embedonix::simplelibs::utilities::benchmark::measure::
                  function_average_execution_time(testsPerFile,
                                                  read_file,
                                                  files[i].data())
                  << "\n";

        std::cout << "read_file_string:\t\t\t" <<
                  embedonix::simplelibs::utilities::benchmark::measure::
                  function_average_execution_time(testsPerFile,
                                                  read_file_string,
                                                  files[i].data())
                  << "\n";
    }

    return 0;
}
