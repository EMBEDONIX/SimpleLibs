cmake_minimum_required(VERSION 3.5...3.20)

project(embedonix_simplelibs_tests VERSION 0.1.0 LANGUAGES CXX)

add_executable(csvparser_tests
        csvparser_tests.cpp)

target_compile_features(csvparser_tests PRIVATE cxx_std_20)
target_link_libraries(csvparser_tests PRIVATE embedonix_simplelibs_parsers)

add_test(NAME csvparser_tests COMMAND csvparser_tests)
