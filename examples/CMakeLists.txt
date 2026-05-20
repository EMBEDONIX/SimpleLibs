# Description: CMake file for SimpleLibs examples
# Author: Saeid Yazdani
# Organization: EMBEDONIX.COM
# Date: 7 May 2023

cmake_minimum_required(VERSION 3.15...3.29)

project(embedonix_simplelibs_examples VERSION 0.1.0 LANGUAGES CXX)

# Get resource dir that resides above current folder
get_filename_component(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

set(RANDOM_FILE_RESOURCES
        "${CMAKE_BINARY_DIR}/resources/random-files/one-mb-file"
        "${CMAKE_BINARY_DIR}/resources/random-files/two-mb-file"
        "${CMAKE_BINARY_DIR}/resources/random-files/ten-mb-file")

set(CSV_FILE_RESOURCES
        "${RESOURCES_DIR}/examples/resources/csv-files/complex-escaped-with-header.csv"
        "${RESOURCES_DIR}/examples/resources/csv-files/simple-no-header.csv")

file(COPY ${CSV_FILE_RESOURCES}
        DESTINATION "${CMAKE_BINARY_DIR}/resources/csv-files")

add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/resources/random-files/one-mb-file"
        COMMAND "${CMAKE_COMMAND}"
        -DOUTPUT="${CMAKE_BINARY_DIR}/resources/random-files/one-mb-file"
        -DSIZE_BYTES=1048576
        -P "${CMAKE_SOURCE_DIR}/cmake/generate_random_file.cmake"
        DEPENDS "${CMAKE_SOURCE_DIR}/cmake/generate_random_file.cmake"
        COMMENT "Generating one-mb-file")

add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/resources/random-files/two-mb-file"
        COMMAND "${CMAKE_COMMAND}"
        -DOUTPUT="${CMAKE_BINARY_DIR}/resources/random-files/two-mb-file"
        -DSIZE_BYTES=2097152
        -P "${CMAKE_SOURCE_DIR}/cmake/generate_random_file.cmake"
        DEPENDS "${CMAKE_SOURCE_DIR}/cmake/generate_random_file.cmake"
        COMMENT "Generating two-mb-file")

add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/resources/random-files/ten-mb-file"
        COMMAND "${CMAKE_COMMAND}"
        -DOUTPUT="${CMAKE_BINARY_DIR}/resources/random-files/ten-mb-file"
        -DSIZE_BYTES=10485760
        -P "${CMAKE_SOURCE_DIR}/cmake/generate_random_file.cmake"
        DEPENDS "${CMAKE_SOURCE_DIR}/cmake/generate_random_file.cmake"
        COMMENT "Generating ten-mb-file")

add_custom_target(example_random_files
        DEPENDS ${RANDOM_FILE_RESOURCES})

# Example fileio
add_executable(fileio
        fileio/fileio.cpp)

target_link_libraries(fileio PRIVATE embedonix_simplelibs_fileio
        PRIVATE embedonix_simplelibs_utilities)
add_dependencies(fileio example_random_files)

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
