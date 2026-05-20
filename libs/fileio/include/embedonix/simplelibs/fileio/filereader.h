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
 * @brief Read a file as raw bytes.
 * @param filepath Path to the file to read.
 * @return File content as a `std::byte` vector.
 * @throws std::ios_base::failure If the file cannot be opened or read.
 */
auto read_file_bytes(std::string_view filepath) -> std::vector<std::byte>;

/**
 * @overload
 */
auto read_file_bytes(const std::string& filepath) -> std::vector<std::byte>;

/**
 * @overload
 */
auto read_file_bytes(const char* filepath) -> std::vector<std::byte>;

/**
 * @overload
 */
auto read_file_bytes(const std::filesystem::path& filepath) -> std::vector<std::byte>;

/**
 * @brief Read a file into a caller owned byte buffer.
 * @param filepath Path to the file to read.
 * @param buffer Destination buffer. It must already be large enough.
 * @return Number of bytes read.
 * @throws std::length_error If `buffer` is smaller than the file.
 * @throws std::ios_base::failure If the file cannot be opened or read.
 */
auto read_file_bytes_into(std::string_view filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;

/**
 * @overload
 */
auto read_file_bytes_into(const std::string& filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;

/**
 * @overload
 */
auto read_file_bytes_into(const char* filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;

/**
 * @overload
 */
auto read_file_bytes_into(const std::filesystem::path& filepath,
                          std::vector<std::byte>& buffer) -> std::size_t;

/**
 * @brief Read a file into a caller owned byte buffer.
 * @param filepath Path to the file to read.
 * @param buffer Destination buffer. It must already be large enough.
 * @return `false` when `buffer` is too small, otherwise `true`.
 * @throws std::ios_base::failure If the file cannot be opened or read.
 *
 * This compatibility wrapper preserves the old bool result while letting
 * normal I/O errors still throw.
 */
auto read_file_bytes_caller_alloc(std::string_view filepath,
                                std::vector<std::byte>& buffer) -> bool;

/**
 * @overload
 */
auto read_file_bytes_caller_alloc(const std::string& filepath,
                                  std::vector<std::byte>& buffer) -> bool;

/**
 * @overload
 */
auto read_file_bytes_caller_alloc(const char* filepath,
                                  std::vector<std::byte>& buffer) -> bool;

/**
 * @overload
 */
auto read_file_bytes_caller_alloc(const std::filesystem::path& filepath,
                                  std::vector<std::byte>& buffer) -> bool;

/**
 * @brief Read a text file into a string.
 * @param path Path to the file to read.
 * @return File content as a string.
 * @throws std::ios_base::failure If the file cannot be opened or read.
 */
auto read_file(std::string_view path) -> std::string;

/**
 * @overload
 */
auto read_file(const std::string& path) -> std::string;

/**
 * @overload
 */
auto read_file(const char* path) -> std::string;

/**
 * @overload
 */
auto read_file(const std::filesystem::path& path) -> std::string;

/**
 * @brief Read a file as bytes and return the same data as a string.
 * @param filepath Path to the file to read.
 * @return File content as a string.
 * @throws std::ios_base::failure If the file cannot be opened or read.
 */
auto read_file_string(std::string_view filepath) -> std::string;

/**
 * @overload
 */
auto read_file_string(const std::string& filepath) -> std::string;

/**
 * @overload
 */
auto read_file_string(const char* filepath) -> std::string;

/**
 * @overload
 */
auto read_file_string(const std::filesystem::path& filepath) -> std::string;

} // End Namespace embedonix::simplelibs::fileio::readers
