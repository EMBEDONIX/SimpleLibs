# Description: CMake file for SimpleLibs Math Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 21 Apr 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_math VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# Add library to be compiled
add_library(embedonix_simplelibs_math INTERFACE)
add_library(embedonix::simplelibs::math ALIAS embedonix_simplelibs_math)

set_target_properties(embedonix_simplelibs_math PROPERTIES
        EXPORT_NAME math)

target_compile_features(embedonix_simplelibs_math INTERFACE cxx_std_20)
# Use source-tree includes while building and install-tree includes after install.
target_include_directories(embedonix_simplelibs_math INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Add this target to the package export set.
install(TARGETS embedonix_simplelibs_math
        EXPORT embedonix_simplelibs_targets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Copy header files to cmake install prefix under include directory
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING
        PATTERN "*.h")
