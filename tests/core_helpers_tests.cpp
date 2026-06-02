#include <embedonix/simplelibs/fileio/filereader.h>
#include <embedonix/simplelibs/math/basic.h>
#include <embedonix/simplelibs/stringtools/print.h>
#include <embedonix/simplelibs/stringtools/split.h>
#include <embedonix/simplelibs/stringtools/trim.h>
#include <embedonix/simplelibs/utilities/benchmark.h>

#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace {
template<typename T>
void expect_equal(const T& actual, const T& expected, const char* name) {
    if (actual != expected) {
        throw std::runtime_error(name);
    }
}

void expect_true(bool value, const char* name) {
    if (!value) {
        throw std::runtime_error(name);
    }
}

void write_file(const std::filesystem::path& path, std::string_view content) {
    auto stream = std::ofstream(path, std::ios::binary);
    stream.write(content.data(), static_cast<std::streamsize>(content.size()));
}
} // namespace

int main() {
    namespace fileio = embedonix::simplelibs::fileio::readers;
    namespace math = embedonix::simplelibs::math::basic_operations;
    namespace print = embedonix::simplelibs::stringtools::print;
    namespace split = embedonix::simplelibs::stringtools::split;
    namespace trim = embedonix::simplelibs::stringtools::trim;
    namespace benchmark = embedonix::simplelibs::utilities::benchmark::measure;

    static_assert(math::is_even(2));
    static_assert(math::is_odd(3));
    static_assert(!math::IntegralNumber<bool>);

    const auto parts = split::by_token(std::string_view{"a,b,"}, ',');
    expect_equal(parts, std::vector<std::string_view>{"a", "b", ""}, "char split");

    const auto splitSource = std::string{"aa--bb--"};
    const auto stringParts = split::by_token(splitSource, "--");
    expect_equal(stringParts, std::vector<std::string_view>{"aa", "bb", ""}, "string split");

    auto padded = std::string{" \tvalue\r\n"};
    trim::both_sides(padded);
    expect_equal(padded, std::string{"value"}, "trim both sides");
    expect_equal(trim::left_copy("  left"), std::string{"left"}, "left trim copy");
    expect_equal(trim::right_copy("right  "), std::string{"right"}, "right trim copy");
    expect_equal(trim::both_sides_copy(" \t\n"), std::string{}, "trim whitespace only");

    auto stream = std::ostringstream();
    print::container(std::vector<int>{1, 2, 3}, ',', false, stream);
    expect_equal(stream.str(), std::string{"1,2,3"}, "container print");

    // Use a unique path so parallel test runs from different build trees do not collide.
    const auto tempName = "embedonix_simplelibs_tests_" +
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    auto tempDir = std::filesystem::temp_directory_path() / tempName;
    std::filesystem::create_directories(tempDir);

    const auto textPath = tempDir / "text.txt";
    const auto emptyPath = tempDir / "empty.txt";

    write_file(textPath, "hello");
    write_file(emptyPath, "");

    expect_equal(fileio::read_file(textPath.string()), std::string{"hello"}, "read_file");
    expect_equal(fileio::read_file_string(emptyPath.string()), std::string{}, "empty string file");
    expect_equal(fileio::read_file_bytes(emptyPath.string()).size(), std::size_t{0}, "empty byte file");

    auto smallBuffer = std::vector<std::byte>(2);
    expect_true(!fileio::read_file_bytes_caller_alloc(textPath.string(), smallBuffer),
                "small caller buffer");
    auto tooSmallThrew = false;
    try {
        fileio::read_file_bytes_into(textPath, smallBuffer);
    } catch (const std::length_error&) {
        tooSmallThrew = true;
    }
    expect_true(tooSmallThrew, "small buffer throws");

    auto buffer = std::vector<std::byte>(5);
    expect_equal(fileio::read_file_bytes_into(textPath, buffer), std::size_t{5},
                 "bytes read count");
    expect_true(buffer[0] == std::byte{'h'} && buffer[4] == std::byte{'o'},
                "caller buffer content");

    auto timer = std::chrono::time_point<std::chrono::steady_clock>{};
    benchmark::start_timer(timer);
    const auto elapsed = benchmark::stop_timer<std::chrono::steady_clock>(timer);
    (void)elapsed;
    expect_equal(benchmark::format_duration(std::chrono::milliseconds{7}), std::string{"7ms"},
                 "format duration compact");
    expect_equal(benchmark::format_duration(std::chrono::microseconds{11}, true),
                 std::string{"11 us"}, "format duration spaced");

    auto threw = false;
    try {
        benchmark::function_average_execution_time(0, [] {});
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    expect_true(threw, "zero benchmark runs");

    std::filesystem::remove_all(tempDir);

    return 0;
}
