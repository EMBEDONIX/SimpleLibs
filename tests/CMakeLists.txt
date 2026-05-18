cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_tests VERSION 0.1.0 LANGUAGES CXX)

add_executable(csvparser_tests
        csvparser_tests.cpp)

target_compile_features(csvparser_tests PRIVATE cxx_std_20)
target_link_libraries(csvparser_tests PRIVATE embedonix_simplelibs_parsers)

add_test(NAME csvparser_tests COMMAND csvparser_tests)

add_executable(core_helpers_tests
        core_helpers_tests.cpp)

target_compile_features(core_helpers_tests PRIVATE cxx_std_20)
target_link_libraries(core_helpers_tests
        PRIVATE embedonix_simplelibs_fileio
        PRIVATE embedonix_simplelibs_math
        PRIVATE embedonix_simplelibs_stringtools
        PRIVATE embedonix_simplelibs_utilities)

add_test(NAME core_helpers_tests COMMAND core_helpers_tests)
