#include <embedonix/simplelibs/parsers/csvparser.h>

#include <stdexcept>
#include <string>
#include <vector>

namespace {
using Table = std::vector<std::vector<std::string>>;

void expect_equal(const Table& actual, const Table& expected, const char* name) {
    if (actual != expected) {
        throw std::runtime_error(name);
    }
}
} // namespace

int main() {
    using embedonix::simplelibs::parsers::csv_file;
    using embedonix::simplelibs::parsers::csv_file_with_wrapper;

    expect_equal(csv_file("a,b,c\n1,2,3"),
                 {{"a", "b", "c"}, {"1", "2", "3"}},
                 "simple csv");

    expect_equal(csv_file("a,b,\n,,"),
                 {{"a", "b", ""}, {"", "", ""}},
                 "empty fields");

    expect_equal(csv_file_with_wrapper("name,notes\n\"alpha\",\"one,two\"", ',', '"'),
                 {{"alpha", "one,two"}},
                 "quoted delimiter");

    expect_equal(csv_file_with_wrapper("name,notes\n\"alpha\",\"one,two\"", ',', '"', false),
                 {{"name", "notes"}, {"alpha", "one,two"}},
                 "keep header");

    expect_equal(csv_file_with_wrapper("\"only\"\n", ',', '"', false),
                 {{"only"}},
                 "single wrapped field");

    expect_equal(csv_file_with_wrapper("name|notes\n'alpha'|'one|two'", '|', '\'', false),
                 {{"name", "notes"}, {"alpha", "one|two"}},
                 "custom delimiter and wrapper");

    expect_equal(csv_file_with_wrapper("name,quote\n\"alpha\",\"say \"\"hi\"\"\"", ',', '"'),
                 {{"alpha", "say \"hi\""}},
                 "escaped wrapper");

    expect_equal(csv_file_with_wrapper("name,notes\r\n\"alpha\",\"line 1\r\nline 2\"", ',', '"'),
                 {{"alpha", "line 1\r\nline 2"}},
                 "quoted newline");

    const auto malformed = embedonix::simplelibs::parsers::try_csv_file_with_wrapper(
        "name,notes\n\"alpha\",\"unterminated", ',', '"');
    if (!malformed.has_error() ||
        malformed.error != embedonix::simplelibs::parsers::csv_parse_error::unclosed_wrapped_field) {
        throw std::runtime_error("malformed csv result");
    }

    auto threw = false;
    try {
        (void)csv_file_with_wrapper("name,notes\n\"alpha\",\"unterminated", ',', '"');
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    if (!threw) {
        throw std::runtime_error("malformed csv throw");
    }

    return 0;
}
