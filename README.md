# EMBEDONIX SimpleLibs

SimpleLibs is a small collection of C++ helper libraries for code that tends to get repeated across projects.

The project is still early, but the goal is to keep the APIs small, readable, and useful in normal C++ projects.

## Modules

- `math`: small numeric helpers.
- `fileio`: helpers for reading files as text or bytes.
- `parsers`: simple parsers, currently focused on CSV.
- `stringtools`: trim, split, and print helpers for strings and containers.
- `utilities`: small utility helpers such as timing functions.

## Requirements

- C++20
- CMake 3.15 or newer

## Build

```sh
cmake -S . -B build
cmake --build build
```

Examples are built by default. To build only the libraries and tests:

```sh
cmake -S . -B build -DBUILD_EXAMPLES=OFF
cmake --build build
```

## Tests

```sh
ctest --test-dir build --output-on-failure
```

## Install And Use With CMake

```sh
cmake -S . -B build -DBUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=/path/to/install
cmake --build build
cmake --install build
```

Then consume it from another CMake project:

```cmake
find_package(embedonix_simplelibs CONFIG REQUIRED)

target_link_libraries(app PRIVATE
    embedonix::simplelibs::math
    embedonix::simplelibs::fileio
    embedonix::simplelibs::parsers
    embedonix::simplelibs::stringtools
    embedonix::simplelibs::utilities)
```

## Quick Example

```cpp
#include <embedonix/simplelibs/parsers/csvparser.h>

#include <iostream>

int main() {
    const auto csv = "name,role\n"
                     "\"Saeid\",\"developer\"";

    const auto rows = embedonix::simplelibs::parsers::csv_file_with_wrapper(csv);

    for (const auto& row : rows) {
        for (const auto& field : row) {
            std::cout << field << '\n';
        }
    }
}
```

## License

This project is licensed under GPLv3. See `LICENSE` for the full license text.
