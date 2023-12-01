#include <catch2/catch_all.hpp>
#include <semver/semver.hpp>
#include <sstream>

TEST_CASE("Test version std::ostream <<", "[version]") {
    semver::version v = semver::version::parse("5.2.3");
    std::stringstream ss;
    ss << v;
    REQUIRE(ss.str() == "5.2.3");
}

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
