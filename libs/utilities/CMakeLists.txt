# Description: CMake file for SimpleLibs Parsers Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 21 Apr 2023

cmake_minimum_required(VERSION 3.5...3.20)

project(embedonix_simplelibs_utilities VERSION 0.1.0 LANGUAGES CXX)

# Add library to be compiled
add_library(embedonix_simplelibs_utilities INTERFACE
        ./include/embedonix/simplelibs/utilities/benchmark.h)
add_library(embedonix::simplelibs::utilities ALIAS embedonix_simplelibs_utilities)

target_compile_features(embedonix_simplelibs_utilities INTERFACE cxx_std_20)
target_include_directories(embedonix_simplelibs_utilities INTERFACE include)

install(TARGETS embedonix_simplelibs_utilities
        # CONFIGURATIONS Debug ## Commented out because I want same for both releaes and debug
        DESTINATION /) # will be root of cmake install prefix

# Copy header files to cmake install prefix under include directory
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h")
