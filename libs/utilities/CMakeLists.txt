# Description: CMake file for SimpleLibs Utilities Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 21 Apr 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_utilities VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# Add library to be compiled
add_library(embedonix_simplelibs_utilities INTERFACE)
add_library(embedonix::simplelibs::utilities ALIAS embedonix_simplelibs_utilities)

set_target_properties(embedonix_simplelibs_utilities PROPERTIES
        EXPORT_NAME utilities)

target_compile_features(embedonix_simplelibs_utilities INTERFACE cxx_std_20)
# Use source-tree includes while building and install-tree includes after install.
target_include_directories(embedonix_simplelibs_utilities INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Add this target to the package export set.
install(TARGETS embedonix_simplelibs_utilities
        EXPORT embedonix_simplelibs_targets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Copy header files to cmake install prefix under include directory
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING
        PATTERN "*.h")
