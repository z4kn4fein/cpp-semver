/*
License: MIT (http://opensource.org/licenses/MIT).

Copyright (c) 2024 Peter Csajtai <peter.csajtai@outlook.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

module;

#include <ostream>
#include <string>
#include <regex>
#include <utility>
#include <vector>

#ifdef __cpp_lib_format
#if __cpp_lib_format >= 201907L
#include <format>
#include <string_view>
#endif
#endif

export module semver;

#define SEMVER_MODULE

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 5244)
#endif

#ifdef __clang__
#pragma clang diagnostic push
#if __has_warning("-Winclude-angled-in-module-purview")
#pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif
#endif

#include <semver/semver.hpp>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
