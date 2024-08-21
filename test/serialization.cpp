#include <catch2/catch_test_macros.hpp>
#include <sstream>

#ifdef SEMVER_TEST_MODULE
import semver;
#else
#include <semver/semver.hpp>
#endif

TEST_CASE("Test version std::ostream <<", "[version]") {
    semver::version v = semver::version::parse("5.2.3");
    std::stringstream ss;
    ss << v;
    REQUIRE(ss.str() == "5.2.3");
}

#ifndef SEMVER_TEST_MODULE
#ifdef __cpp_lib_format
#if __cpp_lib_format >= 201907L

TEST_CASE("Test version std::format formatter", "[version]") {
    REQUIRE(std::format("{}", semver::version::parse("5.2.3")) == "5.2.3");
    REQUIRE(std::format("{}", semver::version::parse("5.2.3-alpha")) == "5.2.3-alpha");
    REQUIRE(std::format("{}", semver::version::parse("5.2.3-1.2.3")) == "5.2.3-1.2.3");
    REQUIRE(std::format("{}", semver::version::parse("5.2.3-alpha+build34")) == "5.2.3-alpha+build34");
    REQUIRE(std::format("{}", semver::version::parse("5.2.3-1.2.3+build34")) == "5.2.3-1.2.3+build34");
}

#endif
#endif
#endif
