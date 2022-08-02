#include <catch2/catch_all.hpp>
#include <semver/semver.hpp>

TEST_CASE("Test invalid pre-releases", "[prerelease]") {
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse(".alpha"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse("alpha."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse(".alpha."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse("alpha. "), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse("alpha.01"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse("+alpha.01"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::prerelease_descriptor::parse("%alpha"), semver::semver_exception);
}

TEST_CASE("Test pre-release increment", "[prerelease]") {
    REQUIRE(semver::prerelease_descriptor::parse("alpha-3.Beta").increment().str() == "alpha-3.Beta.0");
    REQUIRE(semver::prerelease_descriptor::parse("alpha-3.13.Beta").increment().str() == "alpha-3.14.Beta");
    REQUIRE(semver::prerelease_descriptor::parse("alpha.5.Beta.7").increment().str() == "alpha.5.Beta.8");
}

TEST_CASE("Test pre-release equality", "[prerelease]") {
    REQUIRE(semver::prerelease_descriptor::parse("alpha-3.Beta.0").str() == "alpha-3.Beta.0");
    REQUIRE(semver::prerelease_descriptor::parse("alpha-3.Beta.0") == semver::prerelease_descriptor::parse("alpha-3.Beta.0"));
    REQUIRE(semver::prerelease_descriptor::parse("alpha-3.Beta.0") != semver::prerelease_descriptor::parse("alpha-3.Beta.1"));
}

TEST_CASE("Test pre-release default", "[prerelease]") {
    REQUIRE(semver::prerelease_descriptor::initial().str() == "0");
    REQUIRE(semver::prerelease_descriptor::empty().is_empty());
}