//
// Created by Saeid Yazdani on 4/23/2023.
//

#include "embedonix/simplelibs/fileio/filereader.h"

#include <fstream>
#include <stdexcept>

namespace embedonix::simplelibs::fileio::readers {

auto read_file_bytes(const std::filesystem::path& filepath) -> std::vector<std::byte> {
  // Open at the end first so tellg can give the exact file size before reading.
  std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);

  if (!ifs)
    throw std::ios_base::failure("File does not exist");

  const auto end = ifs.tellg();
  if (end < 0)
    throw std::ios_base::failure("Read error");

  ifs.seekg(0, std::ios::beg);

  const auto size = static_cast<std::size_t>(end - ifs.tellg());

  if (size == 0) // avoid undefined behavior
    return {};

  std::vector<std::byte> buffer(size);

  if (!ifs.read(reinterpret_cast<char *>(buffer.data()), buffer.size()))
    throw std::ios_base::failure("Read error");

  return buffer;
}

auto read_file_bytes(std::string_view filepath) -> std::vector<std::byte> {
  return read_file_bytes(std::filesystem::path{std::string(filepath)});
}

auto read_file_bytes(const std::string& filepath) -> std::vector<std::byte> {
  return read_file_bytes(std::filesystem::path{filepath});
}

auto read_file_bytes(const char* filepath) -> std::vector<std::byte> {
  return read_file_bytes(std::filesystem::path{filepath});
}

auto read_file_bytes_into(const std::filesystem::path& filepath,
                          std::vector<std::byte>& buffer) -> std::size_t {
    // Keep the caller owned buffer size unchanged. It must already be large enough.
    std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);

    if (!ifs)
        throw std::ios_base::failure("File does not exist");

    const auto end = ifs.tellg();
    if (end < 0)
        throw std::ios_base::failure("Read error");

    ifs.seekg(0, std::ios::beg);

    const auto size = static_cast<std::size_t>(end - ifs.tellg());

    if (size == 0)
        return 0;

    if (buffer.size() < size)
        throw std::length_error("Buffer is smaller than file");

    if (!ifs.read(reinterpret_cast<char *>(buffer.data()), size))
        throw std::ios_base::failure("Read error");

    return size;
}

auto read_file_bytes_into(std::string_view filepath,
                          std::vector<std::byte>& buffer) -> std::size_t {
    return read_file_bytes_into(std::filesystem::path{std::string(filepath)}, buffer);
}

auto read_file_bytes_into(const std::string& filepath,
                          std::vector<std::byte>& buffer) -> std::size_t {
    return read_file_bytes_into(std::filesystem::path{filepath}, buffer);
}

auto read_file_bytes_into(const char* filepath,
                          std::vector<std::byte>& buffer) -> std::size_t {
    return read_file_bytes_into(std::filesystem::path{filepath}, buffer);
}

auto read_file_bytes_caller_alloc(std::string_view filepath,
                                            std::vector<std::byte>& buffer)-> bool {
    try {
        read_file_bytes_into(filepath, buffer);
    } catch (const std::length_error&) {
        // Preserve the old bool contract while letting I/O errors still throw.
        return false;
    }

    return true;
}

auto read_file_bytes_caller_alloc(const std::string& filepath,
                                  std::vector<std::byte>& buffer) -> bool {
    return read_file_bytes_caller_alloc(std::string_view{filepath}, buffer);
}

auto read_file_bytes_caller_alloc(const char* filepath,
                                  std::vector<std::byte>& buffer) -> bool {
    return read_file_bytes_caller_alloc(std::string_view{filepath}, buffer);
}

auto read_file_bytes_caller_alloc(const std::filesystem::path& filepath,
                                  std::vector<std::byte>& buffer) -> bool {
    try {
        read_file_bytes_into(filepath, buffer);
    } catch (const std::length_error&) {
        // Preserve the old bool contract while letting I/O errors still throw.
        return false;
    }

    return true;
}

auto read_file(const std::filesystem::path& path) -> std::string {
  constexpr auto read_size = std::size_t(4096);
  auto stream = std::ifstream(path);
  stream.exceptions(std::ios_base::badbit);

  if (not stream) {
    throw std::ios_base::failure("File does not exist");
  }

  auto out = std::string();
  auto buf = std::string(read_size, '\0');
  while (stream.read(&buf[0], read_size)) {
    out.append(buf, 0, stream.gcount());
  }
  out.append(buf, 0, stream.gcount());
  return out;
}

auto read_file(std::string_view path) -> std::string {
  return read_file(std::filesystem::path{std::string(path)});
}

auto read_file(const std::string& path) -> std::string {
  return read_file(std::filesystem::path{path});
}

auto read_file(const char* path) -> std::string {
  return read_file(std::filesystem::path{path});
}

auto read_file_string(const std::filesystem::path& filepath) -> std::string {
  auto bytes = read_file_bytes(filepath);
  if (bytes.empty())
    return {};

  return std::string(reinterpret_cast<const char *>(bytes.data()), bytes.size());
}

auto read_file_string(std::string_view filepath) -> std::string {
  return read_file_string(std::filesystem::path{std::string(filepath)});
}

auto read_file_string(const std::string& filepath) -> std::string {
  return read_file_string(std::filesystem::path{filepath});
}

auto read_file_string(const char* filepath) -> std::string {
  return read_file_string(std::filesystem::path{filepath});
}



} // End Namespace embedonix::simplelibs::fileio::readers
