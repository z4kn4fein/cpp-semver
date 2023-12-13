# cpp-semver

[![Build](https://img.shields.io/github/actions/workflow/status/z4kn4fein/cpp-semver/ci.yml?logo=GitHub&label=windows%20%2F%20macos%20%2F%20linux&branch=main)](https://github.com/z4kn4fein/cpp-semver/actions/workflows/ci.yml)
[![Build](https://img.shields.io/github/actions/workflow/status/z4kn4fein/cpp-semver/sanitize.yml?logo=GitHub&label=sanitize&branch=main)](https://github.com/z4kn4fein/cpp-semver/actions/workflows/sanitize.yml)
[![codecov](https://codecov.io/gh/z4kn4fein/cpp-semver/branch/main/graph/badge.svg?token=N3EF1SOX18)](https://codecov.io/gh/z4kn4fein/cpp-semver)
[![vcpkg](https://img.shields.io/badge/package-vcpkg-blue)](https://github.com/microsoft/vcpkg/tree/master/ports/z4kn4fein-semver)
[![godbolt](https://img.shields.io/badge/try-on_godbolt-blue)](https://godbolt.org/z/ad9YYdc91)

Semantic Versioning library for modern C++.
It implements the full [semantic version 2.0.0](https://semver.org/spec/v2.0.0.html) specification and
provides the ability to **parse**, **compare**, and **increment** semantic versions.

## Features
- C++17
- Single-file / header-only
- No external dependencies

## Installation
1. Include `semver.hpp`

   As `semver` is a header-only library, you can download and copy [`semver.hpp`](https://github.com/z4kn4fein/cpp-semver/blob/main/include/semver/semver.hpp) 
   to your project's include path.

2. With `cmake`

   ```cmake
   include(FetchContent)
   
   FetchContent_Declare(
       cpp-semver
       GIT_REPOSITORY https://github.com/z4kn4fein/cpp-semver.git
       GIT_TAG v0.3.3)
   FetchContent_MakeAvailable(cpp-semver)
   ```

   This will produce the target `semver` which you can link against the typical way:

   ```cmake
   target_link_libraries(your_target_name PRIVATE semver)
   ```
3. With `vcpkg`

   If you are using vcpkg for external dependencies, then you can install the package with:
   ```bash
   vcpkg install z4kn4fein-semver
   ```

## Usage
The following options are available to construct a `version`:
1. Building part by part.

   ```cpp
   auto version = semver::version(3, 5, 2, "alpha", "build");
   ```

2. Parsing from a string with `semver::version::parse()`:

   ```cpp
   auto version = semver::version::parse("3.5.2-alpha+build");
   ```

3. Using the `_v` user-defined literal on a string.

   ```cpp
   using namespace semver::literals; // required to use the literals
   
   auto version = "3.5.2-alpha+build"_v;
   ```

The constructed `version` provides the following information:
```cpp
semver::version version = "3.5.2-alpha.2+build"_v;

std::cout << version;                     // 3.5.2-alpha.2+build
std::cout << version.major();             // 3
std::cout << version.minor();             // 5
std::cout << version.patch();             // 2
std::cout << version.prerelease();        // "alpha.2"
std::cout << version.build_meta();        // "build"

std::cout << version.is_prerelease();     // true
std::cout << version.is_stable();         // false

std::cout << version.without_suffixes();  // "3.5.2"
```

### Strict vs. Loose Parsing
By default, the version parser considers partial versions like `1.0` and versions starting with the `v` prefix invalid.
This behaviour can be turned off by setting the parser's `strict` parameter to `false` or by using the `_lv` user-defined literal.
```cpp
std::cout << "v2.3-alpha"_v;                                  // exception
std::cout << "2.1"_v;                                         // exception
std::cout << "v3"_v;                                          // exception

std::cout << semver::version::parse("v2.3-alpha", false);     // 2.3.0-alpha
std::cout << "2.1"_lv;                                        // 2.1.0
std::cout << "v3"_lv;                                         // 3.0.0
```

## Compare

It is possible to compare two `version` objects with comparison operators.
```cpp
"0.1.0"_v < "0.1.1"_v;                   // true
"0.1.1"_v <= "0.1.1"_v;                  // true
"0.1.0-alpha.3"_v < "0.1.0-alpha.4"_v;   // true
```

The equality of two `version` objects can be determined with equality operators.
```cpp
"0.1.1"_v == "0.1.1"_v;       // true
"0.1.1"_v != "0.1.1"_v;       // false
```

## Increment
`version` objects can produce incremented versions of themselves with the `next_major()`,
`next_minor()`, `next_patch()`, `next_prerelease()`, and `increment()` methods.
These methods can be used to determine the next version in order by increasing the appropriate identifier.
`version` objects are **immutable**, so each incrementing function creates a new `version`.

This example shows how the incrementation works on a stable version:
```cpp
auto stable = "1.0.0"_v;

std::cout << stable.next_major();                          // 2.0.0
std::cout << stable.next_minor();                          // 1.1.0
std::cout << stable.next_patch();                          // 1.0.1
std::cout << stable.next_prerelease();                     // 1.0.1-0

// or with the increment() method:
std::cout << stable.increment(semver::inc::major);         // 2.0.0
std::cout << stable.increment(semver::inc::minor);         // 1.1.0
std::cout << stable.increment(semver::inc::patch);         // 1.0.1
std::cout << stable.increment(semver::inc::prerelease);    // 1.0.1-0
```

In case of an unstable version:
```cpp
auto unstable = "1.0.0-alpha.2+build.1"_v;

std::cout << unstable.next_major();                         // 2.0.0
std::cout << unstable.next_minor();                         // 1.1.0
std::cout << unstable.next_patch();                         // 1.0.0
std::cout << unstable.next_prerelease();                    // 1.0.0-alpha.3

// or with the increment() method:
std::cout << unstable.increment(semver::inc::major);        // 2.0.0
std::cout << unstable.increment(semver::inc::minor);        // 1.1.0
std::cout << unstable.increment(semver::inc::patch);        // 1.0.0
std::cout << unstable.increment(semver::inc::prerelease);   // 1.0.0-alpha.3
```

Each incrementing function provides the option to set a pre-release identity on the incremented version.
```cpp
auto version = "1.0.0-alpha.1"_v;

std::cout << version.next_major("beta");                            // 2.0.0-beta
std::cout << version.next_minor("");                                // 1.1.0
std::cout << version.next_patch("alpha");                           // 1.0.1-alpha
std::cout << version.next_prerelease("alpha");                      // 1.0.0-alpha.2

// or with the increment() method:
std::cout << version.increment(semver::inc::major, "beta");         // 2.0.0-beta
std::cout << version.increment(semver::inc::minor, "");             // 1.1.0
std::cout << version.increment(semver::inc::patch, "alpha");        // 1.0.1-alpha
std::cout << version.increment(semver::inc::prerelease, "alpha");   // 1.0.0-alpha.2
```

## Exceptions
When the version parsing fails due to an invalid format, the library throws a specific `semver_exception`.

## Contact & Support
- Create an [issue](https://github.com/z4kn4fein/cpp-semver/issues) for bug reports and feature requests.
- Start a [discussion](https://github.com/z4kn4fein/cpp-semver/discussions) for your questions and ideas.
- Add a ⭐️ to support the project!
