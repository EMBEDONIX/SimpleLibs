//
// Created by Saeid Yazdani on 5/7/2023.
//

#include <iostream>
#include <array>

#include <embedonix/simplelibs/fileio/filereader.h>
#include <embedonix/simplelibs/parsers/csvparser.h>
#include <embedonix/simplelibs/stringtools/trim.h>
#include <embedonix/simplelibs/stringtools/print.h>

using namespace embedonix::simplelibs;

// List of files
constinit auto files = std::array<std::string_view, 1>{
        "../resources/csv-files/complex-escaped-with-header.csv"
};

int main() {
    std::cout << "Welcome to CSVPARSER example!" << std::endl;
    auto content = fileio::readers::read_file(files[0].data());
    //auto data = parsers::csv_file(content);
    auto data = parsers::csv_file_with_wrapper(content, ',', '"');


    for (auto i: data) {
        for (auto j: i) {
            std::cout << j << "\n";
        }
    }

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            std::cout << "[" << i << ", " << j << "] = "
                      << stringtools::trim::both_sides_copy(data[i][j]) << " ";
        }
        std::cout << "\n";
    }

    for (const auto &row: data)
        stringtools::print::container(row, ',');

    return 0;
}
