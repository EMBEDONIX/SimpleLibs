//
// Created by Saeid Yazdani on 05/06/2023.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::stringtools::split {

/**
 * @brief Split a character sequence by a string token.
 * @param content Text to split.
 * @param token Token to split on. An empty token returns `content` unchanged.
 * @return Views into `content`, including empty views for trailing separators.
 *
 * @warning Returned `std::string_view` values borrow from `content`.
 */
inline std::vector<std::string_view> by_token(std::string_view content,
                                              std::string_view token) {
  auto result = std::vector<std::string_view>();

  if (token.empty()) {
    // There is no safe split point for an empty token, so return the full view.
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

/**
 * @overload
 */
inline std::vector<std::string_view> by_token(const std::string& content,
                                              std::string_view token) {
  return by_token(std::string_view{content}, token);
}

/**
 * @brief Deleted overload for temporary strings.
 *
 * Returned views would dangle if a temporary string were accepted.
 */
std::vector<std::string_view> by_token(std::string&& content,
                                       std::string_view token) = delete;

/**
 * @brief Split a character sequence by a character token.
 * @param content Text to split.
 * @param token Character to split on.
 * @return Views into `content`, including empty views for trailing separators.
 *
 * @warning Returned `std::string_view` values borrow from `content`.
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

/**
 * @overload
 */
inline std::vector<std::string_view> by_token(const std::string& content,
                                              char token) {
  return by_token(std::string_view{content}, token);
}

/**
 * @brief Deleted overload for temporary strings.
 *
 * Returned views would dangle if a temporary string were accepted.
 */
std::vector<std::string_view> by_token(std::string&& content, char token) = delete;

} // End namespace namespace embedonix::simplelibs::stringtools
