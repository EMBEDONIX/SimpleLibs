# Description: CMake file for SimpleLibs examples
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 7 May 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_examples VERSION 0.1.0 LANGUAGES CXX)

# Get resource dir that resides above current folder
get_filename_component(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

set(RANDOM_FILE_RESOURCES
        "${RESOURCES_DIR}/examples/resources/random-files/one-mb-file"
        "${RESOURCES_DIR}/examples/resources/random-files/two-mb-file"
        "${RESOURCES_DIR}/examples/resources/random-files/ten-mb-file")

set(CSV_FILE_RESOURCES
        "${RESOURCES_DIR}/examples/resources/csv-files/complex-escaped-with-header.csv"
        "${RESOURCES_DIR}/examples/resources/csv-files/simple-no-header.csv")

# Copy only known example fixtures into the build tree.
file(COPY ${RANDOM_FILE_RESOURCES}
        DESTINATION "${CMAKE_BINARY_DIR}/resources/random-files")
file(COPY ${CSV_FILE_RESOURCES}
        DESTINATION "${CMAKE_BINARY_DIR}/resources/csv-files")

# Example fileio
add_executable(fileio
        fileio/fileio.cpp)

target_link_libraries(fileio PRIVATE embedonix_simplelibs_fileio
        PRIVATE embedonix_simplelibs_utilities)

install(FILES ${RANDOM_FILE_RESOURCES}
        DESTINATION "resources/random-files")

# Example csvparsers
add_executable(csvparser
        parsers/csvparser.cpp)

target_link_libraries(csvparser PRIVATE embedonix_simplelibs_parsers
        PRIVATE embedonix_simplelibs_fileio
        PRIVATE embedonix_simplelibs_stringtools)

install(FILES ${CSV_FILE_RESOURCES}
        DESTINATION "resources/csv-files")

add_executable(math
        math/math.cpp)
target_link_libraries(math PRIVATE embedonix_simplelibs_math
        PRIVATE embedonix_simplelibs_stringtools)
