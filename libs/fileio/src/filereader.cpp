//
// Created by Saeid Yazdani on 4/23/2023.
//

#include "embedonix/simplelibs/fileio/filereader.h"
#include <fstream>

namespace embedonix::simplelibs::fileio::readers {

auto read_file_bytes(std::string_view filepath) -> std::vector<std::byte> {
  std::ifstream ifs(filepath.data(), std::ios::binary | std::ios::ate);

  if (!ifs)
    throw std::ios_base::failure("File does not exist");

  const auto end = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  const auto size = static_cast<std::size_t>(end - ifs.tellg());

  if (size == 0) // avoid undefined behavior
    return {};

  std::vector<std::byte> buffer(size);

  if (!ifs.read(reinterpret_cast<char *>(buffer.data()), buffer.size()))
    throw std::ios_base::failure("Read error");

  return buffer;
}

auto read_file_bytes_caller_alloc(std::string_view filepath,
                                            std::vector<std::byte>& buffer)-> bool {
    std::ifstream ifs(filepath.data(), std::ios::binary | std::ios::ate);

    if (!ifs)
        throw std::ios_base::failure("File does not exist");

    auto end = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto size = std::size_t(end - ifs.tellg());

    if (size == 0) // avoid undefined behavior
        return false;
    size_t countToRead = size > buffer.size() ? buffer.size() : size;

    if (!ifs.read((char *) buffer.data(), countToRead))
        throw std::ios_base::failure("Read error");

    return true;
}

auto read_file(std::string_view path) -> std::string {
  constexpr auto read_size = std::size_t(4096);
  auto stream = std::ifstream(path.data());
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

auto read_file_string(std::string_view filepath) -> std::string {
  auto bytes = read_file_bytes(filepath);
  return std::string(reinterpret_cast<char *>(&bytes[0]), bytes.size());
}



} // End Namespace embedonix::simplelibs::fileio::readers
