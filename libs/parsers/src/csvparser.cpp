//
// Created by Saeid Yazdani on 4/22/2023.
//

#include "embedonix/simplelibs/parsers/csvparser.h"

#include <cctype>
#include <stdexcept>

namespace embedonix::simplelibs::parsers {

namespace {
csv_parse_result parse_csv(std::string_view source,
                           char delimiter,
                           char wrapper,
                           bool useWrapper) {
    auto rows = std::vector<std::vector<std::string>>();
    auto row = std::vector<std::string>();
    auto field = std::string();

    // Parser state for quoted fields. A closed wrapper can still be followed by
    // spaces before the delimiter or row ending.
    auto inWrappedField = false;
    auto fieldStarted = false;
    auto wrapperClosed = false;

    auto finishField = [&]() {
        row.push_back(field);
        field.clear();
        fieldStarted = false;
        wrapperClosed = false;
    };

    auto finishRow = [&]() {
        finishField();
        rows.push_back(row);
        row.clear();
    };

    for (auto i = std::size_t{0}; i < source.size(); ++i) {
        const auto current = source[i];

        // Inside a wrapped field, delimiters and newlines are regular content.
        // A doubled wrapper is treated as one literal wrapper character.
        if (inWrappedField) {
            if (current == wrapper) {
                const auto nextIsEscapedWrapper =
                    i + 1 < source.size() && source[i + 1] == wrapper;

                if (nextIsEscapedWrapper) {
                    field.push_back(wrapper);
                    ++i;
                } else {
                    inWrappedField = false;
                    wrapperClosed = true;
                }
            } else {
                field.push_back(current);
            }

            fieldStarted = true;
            continue;
        }

        // A wrapper only starts a quoted field when it is the first character
        // of that field. Later wrappers are treated as ordinary content.
        if (useWrapper && current == wrapper && not fieldStarted) {
            inWrappedField = true;
            fieldStarted = true;
            continue;
        }

        if (current == delimiter) {
            finishField();
            continue;
        }

        // Outside a wrapped field, delimiters and row endings close the current
        // field. CRLF is treated as one row ending.
        if (current == '\n' || current == '\r') {
            if (current == '\r' && i + 1 < source.size() && source[i + 1] == '\n') {
                ++i;
            }
            finishRow();
            continue;
        }

        if (wrapperClosed) {
            if (std::isspace(static_cast<unsigned char>(current)) != 0) {
                continue;
            }

            return {rows, csv_parse_error::unexpected_character_after_wrapper, i};
        }

        field.push_back(current);
        fieldStarted = true;
        wrapperClosed = false;
    }

    if (inWrappedField) {
        return {rows, csv_parse_error::unclosed_wrapped_field, source.size()};
    }

    // Add the final row when the input does not end with a newline.
    if (fieldStarted || !field.empty() || !row.empty()) {
        finishRow();
    }

    return {rows, csv_parse_error::none, 0};
}
} // End anonymous namespace

std::vector<std::vector<std::string>> csv_file(std::string_view source,
                                               char delimiter) {
    return parse_csv(source, delimiter, '\0', false).rows;
}

csv_parse_result try_csv_file_with_wrapper(
    std::string_view source, char delimiter, char wrapper, bool skipHeader) {
    auto rows = parse_csv(source, delimiter, wrapper, true);

    if (rows.has_error()) {
        return rows;
    }

    if (skipHeader && !rows.rows.empty()) {
        rows.rows.erase(rows.rows.begin());
    }

    return rows;
}

std::vector<std::vector<std::string>> csv_file_with_wrapper(
    std::string_view source, char delimiter, char wrapper, bool skipHeader) {
    auto result = try_csv_file_with_wrapper(source, delimiter, wrapper, skipHeader);
    if (result.has_error()) {
        throw std::invalid_argument("Malformed CSV input");
    }

    return result.rows;
}
} // End Namespace embedonix::simplelibs::parsers
