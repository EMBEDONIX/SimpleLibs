//
// Created by Saeid Yazdani on 4/23/2023.
//

#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::fileio::readers {

/**
 * Read a file as raw vector of std::byte
 * @param filepath Path to the file to read
 * @return Content of the file as raw std::byte vector
 */
auto read_file_bytes(std::string_view filepath) -> std::vector<std::byte>;
auto read_file_bytes(const std::string& filepath) -> std::vector<std::byte>;
auto read_file_bytes(const char* filepath) -> std::vector<std::byte>;
auto read_file_bytes(const std::filesystem::path& filepath) -> std::vector<std::byte>;

auto read_file_bytes_into(std::string_view filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;
auto read_file_bytes_into(const std::string& filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;
auto read_file_bytes_into(const char* filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;
auto read_file_bytes_into(const std::filesystem::path& filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;

auto read_file_bytes_caller_alloc(std::string_view filepath,
                                std::vector<std::byte>& buffer) -> bool;
auto read_file_bytes_caller_alloc(const std::string& filepath,
                                  std::vector<std::byte>& buffer) -> bool;
auto read_file_bytes_caller_alloc(const char* filepath,
                                  std::vector<std::byte>& buffer) -> bool;
auto read_file_bytes_caller_alloc(const std::filesystem::path& filepath,
                                  std::vector<std::byte>& buffer) -> bool;

auto read_file(std::string_view path) -> std::string;
auto read_file(const std::string& path) -> std::string;
auto read_file(const char* path) -> std::string;
auto read_file(const std::filesystem::path& path) -> std::string;

auto read_file_string(std::string_view filepath) -> std::string;
auto read_file_string(const std::string& filepath) -> std::string;
auto read_file_string(const char* filepath) -> std::string;
auto read_file_string(const std::filesystem::path& filepath) -> std::string;

} // End Namespace embedonix::simplelibs::fileio::readers
