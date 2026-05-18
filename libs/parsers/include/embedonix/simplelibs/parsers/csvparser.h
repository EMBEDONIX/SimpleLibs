//
// Created by Saeid Yazdani on 4/22/2023.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::parsers {
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
} // End Namespace embedonix::simplelibs::parsers
