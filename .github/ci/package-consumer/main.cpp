#include <embedonix/simplelibs/math/basic.h>
#include <embedonix/simplelibs/parsers/csvparser.h>
#include <embedonix/simplelibs/stringtools/split.h>
#include <embedonix/simplelibs/utilities/benchmark.h>

#include <chrono>
#include <string_view>

int main() {
    const auto rows = embedonix::simplelibs::parsers::csv_file("a,b\n1,2");
    const auto parts =
        embedonix::simplelibs::stringtools::split::by_token(std::string_view{"a,b"}, ',');
    const auto even = embedonix::simplelibs::math::basic_operations::is_even(2);
    const auto formatted =
        embedonix::simplelibs::utilities::benchmark::measure::format_duration(
            std::chrono::microseconds{2});

    return rows.size() == 2 && parts.size() == 2 && even && formatted == "2us" ? 0 : 1;
}
