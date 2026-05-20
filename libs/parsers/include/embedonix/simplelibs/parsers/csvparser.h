//
// Created by Saeid Yazdani on 4/22/2023.
//

#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace embedonix::simplelibs::parsers {

/**
 * @brief Error codes reported by the non throwing CSV parser.
 */
enum class csv_parse_error {
    /// Parsing completed successfully.
    none,

    /// A wrapped field started but did not close before the end of input.
    unclosed_wrapped_field,

    /// A non whitespace character appeared after a closing wrapper.
    unexpected_character_after_wrapper
};

/**
 * @brief Result returned by `try_csv_file_with_wrapper`.
 */
struct csv_parse_result {
    /// Parsed rows. Empty when parsing fails before a full row is completed.
    std::vector<std::vector<std::string>> rows;

    /// Parse error code.
    csv_parse_error error = csv_parse_error::none;

    /// Character offset where parsing failed. Zero means success.
    std::size_t error_position = 0;

    /**
     * @brief Check whether parsing failed.
     * @return `true` when `error` is not `csv_parse_error::none`.
     */
    [[nodiscard]] bool has_error() const noexcept {
        return error != csv_parse_error::none;
    }
};

/**
 * @brief Parse character separated values without wrapper handling.
 * @param source The content to parse.
 * @param delimiter Separator between fields.
 * @return Parsed rows and fields.
 *
 * @note Use `csv_file_with_wrapper()` when fields may be wrapped.
 */
std::vector<std::vector<std::string>> csv_file(std::string_view source,
                                               char delimiter = ',');

/**
 * @brief Parse character separated values with wrapped field support.
 * @param source The content to parse.
 * @param delimiter Separator between fields.
 * @param wrapper Character used to wrap fields.
 * @param skipHeader When `true`, the first parsed row is removed from results.
 * @return Parsed rows and fields.
 * @throws std::invalid_argument If the input contains malformed wrapped fields.
 *
 * Wrapped fields allow delimiters and newlines inside field content.
 */
std::vector<std::vector<std::string>> csv_file_with_wrapper(
    std::string_view source,
    char delimiter = ',',
    char wrapper = '"',
    bool skipHeader = true);

/**
 * @brief Parse character separated values with wrapped field support.
 * @param source The content to parse.
 * @param delimiter Separator between fields.
 * @param wrapper Character used to wrap fields.
 * @param skipHeader When `true`, the first parsed row is removed from results.
 * @return Parsed rows plus an error code and error position.
 *
 * Use this overload when callers need to inspect malformed input without
 * handling exceptions.
 */
csv_parse_result try_csv_file_with_wrapper(
    std::string_view source,
    char delimiter = ',',
    char wrapper = '"',
    bool skipHeader = true);
} // End Namespace embedonix::simplelibs::parsers
