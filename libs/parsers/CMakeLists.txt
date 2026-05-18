# Description: CMake file for SimpleLibs Parsers Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 21 Apr 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_parsers VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# Add library to be compiled
add_library(embedonix_simplelibs_parsers
        src/csvparser.cpp)
add_library(embedonix::simplelibs::parsers ALIAS embedonix_simplelibs_parsers)

set_target_properties(embedonix_simplelibs_parsers PROPERTIES
        EXPORT_NAME parsers)

target_compile_features(embedonix_simplelibs_parsers PUBLIC cxx_std_20)
# Use source-tree includes while building and install-tree includes after install.
target_include_directories(embedonix_simplelibs_parsers PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Add this target to the package export set and install the built library.
install(TARGETS embedonix_simplelibs_parsers
        EXPORT embedonix_simplelibs_targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Copy header files to cmake install prefix under include directory
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING
        PATTERN "*.h")
