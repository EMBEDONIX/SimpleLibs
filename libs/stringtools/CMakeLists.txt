# Description: CMake file for SimpleLibs StringTools Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 29 Apr 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_stringtools VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# Add library to be compiled
add_library(embedonix_simplelibs_stringtools
        src/trim.cpp
        include/embedonix/simplelibs/stringtools/trim.h
        include/embedonix/simplelibs/stringtools/base.h
        include/embedonix/simplelibs/stringtools/print.h
        include/embedonix/simplelibs/stringtools/split.h)
add_library(embedonix::simplelibs::stringtools ALIAS embedonix_simplelibs_stringtools)

set_target_properties(embedonix_simplelibs_stringtools PROPERTIES
        EXPORT_NAME stringtools)

target_compile_features(embedonix_simplelibs_stringtools PUBLIC cxx_std_20)
# Use source-tree includes while building and install-tree includes after install.
target_include_directories(embedonix_simplelibs_stringtools PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Add this target to the package export set and install the built library.
install(TARGETS embedonix_simplelibs_stringtools
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
