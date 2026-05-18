# Description: Top level CMake file for Embedonix SimpleLibs
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 21 Apr 2023

cmake_minimum_required(VERSION 3.5...3.20)

# The default build type must be set before project()
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR AND NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

set(CMAKE_CXX_STANDARD 20)

option(BUILD_EXAMPLES "Build examples" ON)


project(embedonix_simplelibs
        VERSION 0.1.0 # https://semver.org/spec/v0.1.0.html
        DESCRIPTION "Collection of simple yet useful C++ libraries by EMBEDONIX"
        HOMEPAGE_URL https://www.embedonix.com
        LANGUAGES CXX
        )

include(CTest)

# Add library subfodlers to compile
add_subdirectory(./libs/math)
add_subdirectory(./libs/fileio)
add_subdirectory(./libs/parsers)
add_subdirectory(./libs/stringtools)
add_subdirectory(./libs/utilities)

if(BUILD_EXAMPLES)
    add_subdirectory(./examples)
endif()

if(BUILD_TESTING)
    add_subdirectory(./tests)
endif()


# Some good sources to read
#https://stackoverflow.com/questions/2152077/is-it-possible-to-get-cmake-to-build-both-a-static-and-shared-library-at-the-sam
