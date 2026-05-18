# Description: Top level CMake file for Embedonix SimpleLibs
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 21 Apr 2023

cmake_minimum_required(VERSION 3.15...3.29)

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
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

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

# Export all library targets so installed consumers can use find_package().
install(EXPORT embedonix_simplelibs_targets
        FILE embedonix_simplelibsTargets.cmake
        NAMESPACE embedonix::simplelibs::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/embedonix_simplelibs")

# Generate the package config files installed next to the exported targets.
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/embedonix_simplelibsConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/embedonix_simplelibsConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/embedonix_simplelibs")

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/embedonix_simplelibsConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY SameMajorVersion)

# Install the generated config files used by find_package(embedonix_simplelibs).
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/embedonix_simplelibsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/embedonix_simplelibsConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/embedonix_simplelibs")

# Some good sources to read
#https://stackoverflow.com/questions/2152077/is-it-possible-to-get-cmake-to-build-both-a-static-and-shared-library-at-the-sam
