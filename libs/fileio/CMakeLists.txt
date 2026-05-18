# Description: CMake file for SimpleLibs FILEIO Library
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 23 Apr 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_fileio VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

add_library(embedonix_simplelibs_fileio
        src/filereader.cpp)
add_library(embedonix::simplelibs::fileio ALIAS embedonix_simplelibs_fileio)

set_target_properties(embedonix_simplelibs_fileio PROPERTIES
        EXPORT_NAME fileio)

target_compile_features(embedonix_simplelibs_fileio PUBLIC cxx_std_20)
# Use source-tree includes while building and install-tree includes after install.
target_include_directories(embedonix_simplelibs_fileio PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Add this target to the package export set and install the built library.
install(TARGETS embedonix_simplelibs_fileio
        EXPORT embedonix_simplelibs_targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING
        PATTERN "*.h")
