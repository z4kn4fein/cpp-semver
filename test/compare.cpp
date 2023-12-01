#include <catch2/catch_all.hpp>
#include <semver/semver.hpp>

TEST_CASE("Test version compare, less than, by numbers", "[version][compare]") {
    semver::version v = semver::version::parse("5.2.3");
    REQUIRE(v < semver::version::parse("6.0.0"));
    REQUIRE(v < semver::version::parse("5.3.3"));
    REQUIRE(v < semver::version::parse("5.2.4"));
}

TEST_CASE("Test version compare, less than, by prerelease", "[version][compare]") {
    semver::version v = semver::version::parse("5.2.3-alpha.2");
    REQUIRE(v < semver::version::parse("5.2.3-alpha.2.a")); // by pre-release part count
    REQUIRE(v < semver::version::parse("5.2.3-alpha.3")); // by pre-release number comparison
    REQUIRE(v < semver::version::parse("5.2.3-beta")); // by pre-release alphabetical comparison
    REQUIRE(v <= semver::version::parse("5.2.3-alpha.2"));
}

TEST_CASE("Test version compare, by spec", "[version][compare]") {
    REQUIRE(semver::version::parse("1.0.0") < semver::version::parse("2.0.0"));
    REQUIRE(semver::version::parse("2.0.0") < semver::version::parse("2.1.0"));
    REQUIRE(semver::version::parse("2.1.0") < semver::version::parse("2.1.1"));
    REQUIRE(semver::version::parse("1.0.0-alpha") < semver::version::parse("1.0.0"));
    REQUIRE(semver::version::parse("1.0.0-alpha") < semver::version::parse("1.0.0-alpha.1"));
    REQUIRE(semver::version::parse("1.0.0-alpha.1") < semver::version::parse("1.0.0-alpha.beta"));
    REQUIRE(semver::version::parse("1.0.0-alpha.beta") < semver::version::parse("1.0.0-beta"));
    REQUIRE(semver::version::parse("1.0.0-beta") < semver::version::parse("1.0.0-beta.2"));
    REQUIRE(semver::version::parse("1.0.0-beta.2") < semver::version::parse("1.0.0-beta.11"));
    REQUIRE(semver::version::parse("1.0.0-beta.11") < semver::version::parse("1.0.0-rc.1"));
    REQUIRE(semver::version::parse("1.0.0-rc.1") < semver::version::parse("1.0.0"));
}

TEST_CASE("Test version compare, by prerelease, alphabetical", "[version][compare]") {
    REQUIRE(semver::version::parse("5.2.3-alpha.2") < semver::version::parse("5.2.3-alpha.a"));
    REQUIRE(semver::version::parse("5.2.3-alpha.a") > semver::version::parse("5.2.3-alpha.2"));
}

TEST_CASE("Test version compare, by prerelease & stable", "[version][compare]") {
    REQUIRE(semver::version::parse("5.2.3-alpha") < semver::version::parse("5.2.3"));
    REQUIRE(semver::version::parse("5.2.3") > semver::version::parse("5.2.3-alpha"));
}

TEST_CASE("Test version compare, greater than, by numbers", "[version][compare]") {
    semver::version v = semver::version::parse("5.2.3");
    REQUIRE(v > semver::version::parse("4.0.0"));
    REQUIRE(v > semver::version::parse("5.1.3"));
    REQUIRE(v > semver::version::parse("5.2.2"));
    REQUIRE(v >= semver::version::parse("5.2.3"));
}

TEST_CASE("Test version compare, greater than, by prerelease", "[version][compare]") {
    semver::version v = semver::version::parse("5.2.3-alpha.2");
    REQUIRE(v > semver::version::parse("5.2.3-alpha")); // by pre-release part count
    REQUIRE(v > semver::version::parse("5.2.3-alpha.1")); // by pre-release number comparison
    REQUIRE(v < semver::version::parse("5.2.3-alpha.11")); // by pre-release number comparison
    REQUIRE(v > semver::version::parse("5.2.3-a")); // by pre-release alphabetical comparison
    REQUIRE(v >= semver::version::parse("5.2.3-alpha.2"));
}

TEST_CASE("Test version equality", "[version][compare]") {
    REQUIRE(semver::version::parse("5.2.3-alpha.2") == semver::version::parse("5.2.3-alpha.2"));
    REQUIRE(semver::version::parse("5.2.3-alpha.2") != semver::version::parse("5.2.3-alpha.5"));
    REQUIRE(semver::version::parse("5.2.3") == semver::version::parse("5.2.3"));
    REQUIRE(semver::version::parse("5.2.3") != semver::version::parse("5.2.4"));
    REQUIRE(semver::version::parse("0.0.0") == semver::version::parse("0.0.0"));
    REQUIRE(semver::version::parse("5.2.3-alpha.2+build.34") == semver::version::parse("5.2.3-alpha.2"));
    REQUIRE(semver::version::parse("5.2.3-alpha.2+build.34") == semver::version::parse("5.2.3-alpha.2+build.35"));
}

#ifdef __cpp_impl_three_way_comparison
#if __cpp_impl_three_way_comparison >= 201907L

    TEST_CASE("Test version 3-way compare", "[version][compare]") {
        semver::version v = semver::version::parse("5.2.3");
        REQUIRE((v <=> semver::version::parse("6.0.0")) < 0);
        REQUIRE((v <=> semver::version::parse("4.0.0")) > 0);
        REQUIRE((v <=> semver::version::parse("5.2.3")) == 0);
    }

#endif
#endif
