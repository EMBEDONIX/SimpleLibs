//
// Created by Saeid Yazdani on 4/22/2023.
//

#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::parsers {
enum class csv_parse_error {
    none,
    unclosed_wrapped_field,
    unexpected_character_after_wrapper
};

struct csv_parse_result {
    std::vector<std::vector<std::string>> rows;
    csv_parse_error error = csv_parse_error::none;
    std::size_t error_position = 0;

    [[nodiscard]] bool has_error() const noexcept {
        return error != csv_parse_error::none;
    }
};

/**
 * Parse a Character Separated Value (default delimiter is comma ',').
 * @note If elements are wrapped with a pair of characters, please use \
 * <code>csv_file_with_wrapper()</code>.
 * @param source The content to parse.
 * @param delimiter The separator which separates elements (default is
 * a comma).
 * @param valueWrapper The character that wraps elements (default is none).
 * @return Parsed values as vector of string vector
 */
std::vector<std::vector<std::string>> csv_file(std::string_view source,
                                               char delimiter = ',');

/**
 * Parse a Character Separated Value (default delimiter is comma ',') where
 * elements are wrapped within another pair of characters (default '"'). This
 * is a common method to allow inclusion of delimter character in the elements
 * of a CSV file.
 * Example:
 * "first element of a line","element with *,* inside","last element"
 * @param source The content to parse.
 * @param delimiter The separator which separates elements (default is
 * a comma).
 * @param wrapper The character that wraps elements (default is none).
 * @return Parsed values as vector of string vector
 */
std::vector<std::vector<std::string>> csv_file_with_wrapper(
    std::string_view source,
    char delimiter = ',',
    char wrapper = '"',
    bool skipHeader = true);

csv_parse_result try_csv_file_with_wrapper(
    std::string_view source,
    char delimiter = ',',
    char wrapper = '"',
    bool skipHeader = true);
} // End Namespace embedonix::simplelibs::parsers
