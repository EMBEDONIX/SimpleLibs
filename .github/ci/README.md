# CI Notes

This folder holds small files used by the GitHub Actions CMake workflow.

The workflow builds the project on Linux, Windows, and macOS. It also checks both Debug and Release builds, with examples enabled and disabled.

After building and running the project tests, CI installs the library into a temporary folder. Then it builds the `package-consumer` project from this folder. This makes sure the installed CMake package works for another project using:

```cmake
find_package(embedonix_simplelibs CONFIG REQUIRED)
```

## When Adding A Library

If a new library is added under `libs`, update the package consumer too. Add the new installed target to `package-consumer/CMakeLists.txt`, then include and use a tiny part of it in `package-consumer/main.cpp`.

The goal is not to test every feature there. Normal feature tests belong under `tests`. The package consumer only checks that installed users can find and link the library.

## When CI Fails

Check the failed matrix entry first. The OS, build type, and examples setting are shown in the job name.

Try to reproduce with the same options locally. For example:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF
cmake --build build
ctest --test-dir build --output-on-failure
```

If the failure is in the package consumer step, the issue is probably in install rules, exported targets, or public include paths.
