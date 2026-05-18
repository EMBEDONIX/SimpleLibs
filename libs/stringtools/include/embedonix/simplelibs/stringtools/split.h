//
// Created by Saeid Yazdani on 05/06/2023.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::stringtools::split {

/**
 * Split a string by the given token
 * @param content A Sequence of characters
 * @param token Token to split by
 * @return A Container filled with splitted parts of the content
 */
inline std::vector<std::string_view> by_token(std::string_view content,
                                              std::string_view token) {
  auto result = std::vector<std::string_view>();

  if (token.empty()) {
    result.push_back(content);
    return result;
  }

  auto start = std::size_t{0};
  while (start <= content.size()) {
    const auto tokenPosition = content.find(token, start);
    if (tokenPosition == std::string_view::npos) {
      result.push_back(content.substr(start));
      break;
    }

    result.push_back(content.substr(start, tokenPosition - start));
    start = tokenPosition + token.size();
  }

  return result;
}

inline std::vector<std::string_view> by_token(const std::string& content,
                                              std::string_view token) {
  return by_token(std::string_view{content}, token);
}

std::vector<std::string_view> by_token(std::string&& content,
                                       std::string_view token) = delete;

/**
 * Split a string by the given token
 * @param content A Sequence of characters
 * @param token Token to split by
 * @return A Container filled with splitted parts of the content
 */
inline std::vector<std::string_view> by_token(std::string_view content,
                                              char token) {
  auto result = std::vector<std::string_view>();
  auto start = std::size_t{0};

  while (start <= content.size()) {
    const auto tokenPosition = content.find(token, start);
    if (tokenPosition == std::string_view::npos) {
      result.push_back(content.substr(start));
      break;
    }

    result.push_back(content.substr(start, tokenPosition - start));
    start = tokenPosition + 1;
  }

  return result;
}

inline std::vector<std::string_view> by_token(const std::string& content,
                                              char token) {
  return by_token(std::string_view{content}, token);
}

std::vector<std::string_view> by_token(std::string&& content, char token) = delete;

} // End namespace namespace embedonix::simplelibs::stringtools
