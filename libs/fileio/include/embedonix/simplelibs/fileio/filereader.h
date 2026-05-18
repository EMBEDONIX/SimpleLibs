//
// Created by Saeid Yazdani on 4/23/2023.
//

#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::fileio::readers {

/**
 * Read a file as raw vector of std::byte
 * @param filepath Path to thee file to read
 * @return Content of the file as raw std::byte vector
 */
auto read_file_bytes(std::string_view filepath) -> std::vector<std::byte>;

auto read_file_bytes_caller_alloc(std::string_view filepath,
                                std::vector<std::byte>& buffer) -> bool;

auto read_file(std::string_view path) -> std::string;

auto read_file_string(std::string_view filepath) -> std::string;

} // End Namespace embedonix::simplelibs::fileio::readers
