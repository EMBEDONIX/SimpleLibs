cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_package_consumer LANGUAGES CXX)

find_package(embedonix_simplelibs CONFIG REQUIRED)

add_executable(package_consumer
        main.cpp)

target_link_libraries(package_consumer PRIVATE
        embedonix::simplelibs::fileio
        embedonix::simplelibs::math
        embedonix::simplelibs::parsers
        embedonix::simplelibs::stringtools
        embedonix::simplelibs::utilities)

enable_testing()
add_test(NAME package_consumer COMMAND package_consumer)
