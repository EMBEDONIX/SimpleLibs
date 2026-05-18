# Description: CMake file for SimpleLibs StringTools Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 29 Apr 2023

cmake_minimum_required(VERSION 3.5...3.20)

project(embedonix_simplelibs_stringtools VERSION 0.1.0 LANGUAGES CXX)

# Add library to be compiled
add_library(embedonix_simplelibs_stringtools
        src/trim.cpp
        include/embedonix/simplelibs/stringtools/trim.h
        include/embedonix/simplelibs/stringtools/base.h
        include/embedonix/simplelibs/stringtools/print.h
        include/embedonix/simplelibs/stringtools/split.h)
add_library(embedonix::simplelibs::stringtools ALIAS embedonix_simplelibs_stringtools)

target_compile_features(embedonix_simplelibs_stringtools PUBLIC cxx_std_20)
target_include_directories(embedonix_simplelibs_stringtools PUBLIC include)

install(TARGETS embedonix_simplelibs_stringtools
        # CONFIGURATIONS Debug ## Commented out because I want same for both releaes and debug
        DESTINATION /) # will be root of cmake install prefix

# Copy header files to cmake install prefix under include directory
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h")
