#include <catch2/catch_all.hpp>
#include <semver/semver.hpp>

TEST_CASE("Test version incrementation", "[version][increment]") {
    semver::version v = semver::version::parse("1.2.3-alpha.4+build.3");
    REQUIRE("2.0.0" == v.next_major().str());
    REQUIRE("1.3.0" == v.next_minor().str());
    REQUIRE("1.2.3" == v.next_patch().str());
    REQUIRE("1.2.3-alpha.5" == v.next_prerelease().str());
}

TEST_CASE("Test version incrementation without pre-release", "[version][increment]") {
    semver::version v = semver::version::parse("1.2.3");
    REQUIRE("2.0.0" == v.next_major().str());
    REQUIRE("1.3.0" == v.next_minor().str());
    REQUIRE("1.2.4" == v.next_patch().str());
    REQUIRE("1.2.4-0" == v.next_prerelease().str());
}

TEST_CASE("Test version incrementation without numeric pre-release", "[version][increment]") {
    semver::version v = semver::version::parse("1.2.3-alpha");
    REQUIRE("2.0.0" == v.next_major().str());
    REQUIRE("1.3.0" == v.next_minor().str());
    REQUIRE("1.2.3" == v.next_patch().str());
    REQUIRE("1.2.3-alpha.0" == v.next_prerelease().str());
}

TEST_CASE("Test version incrementation without numeric pre-release, with increment()", "[version][increment]") {
    semver::version v = semver::version::parse("1.2.3-alpha");
    REQUIRE("2.0.0" == v.increment(semver::inc::major).str());
    REQUIRE("1.3.0" == v.increment(semver::inc::minor).str());
    REQUIRE("1.2.3" == v.increment(semver::inc::patch).str());
    REQUIRE("1.2.3-alpha.0" == v.increment(semver::inc::prerelease).str());
}

TEST_CASE("Test version incrementation with invalid pre-release", "[version][increment]") {
    semver::version v = semver::version::parse("1.2.3-alpha");
    REQUIRE_THROWS_AS(v.next_major("01"), semver::semver_exception);
    REQUIRE_THROWS_AS(v.next_minor("01"), semver::semver_exception);
    REQUIRE_THROWS_AS(v.next_patch("01"), semver::semver_exception);
    REQUIRE_THROWS_AS(v.next_prerelease("01"), semver::semver_exception);
}

TEST_CASE("Test version incrementation table", "[version][increment]") {
    auto data = GENERATE(table<std::string, semver::inc, std::string, std::string>({
        {"1.2.3", semver::inc::major, "2.0.0", ""},
        {"1.2.3", semver::inc::minor, "1.3.0", ""},
        {"1.2.3", semver::inc::patch, "1.2.4", ""},
        {"1.2.3-alpha", semver::inc::major, "2.0.0", ""},
        {"1.2.0-0", semver::inc::patch, "1.2.0", ""},
        {"1.2.3-4", semver::inc::major, "2.0.0", ""},
        {"1.2.3-4", semver::inc::minor, "1.3.0", ""},
        {"1.2.3-4", semver::inc::patch, "1.2.3", ""},
        {"1.2.3-alpha.0.beta", semver::inc::major, "2.0.0", ""},
        {"1.2.3-alpha.0.beta", semver::inc::minor, "1.3.0", ""},
        {"1.2.3-alpha.0.beta", semver::inc::patch, "1.2.3", ""},
        {"1.2.4", semver::inc::prerelease, "1.2.5-0", ""},
        {"1.2.3-0", semver::inc::prerelease, "1.2.3-1", ""},
        {"1.2.3-alpha.0", semver::inc::prerelease, "1.2.3-alpha.1", ""},
        {"1.2.3-alpha.1", semver::inc::prerelease, "1.2.3-alpha.2", ""},
        {"1.2.3-alpha.2", semver::inc::prerelease, "1.2.3-alpha.3", ""},
        {"1.2.3-alpha.0.beta", semver::inc::prerelease, "1.2.3-alpha.1.beta", ""},
        {"1.2.3-alpha.1.beta", semver::inc::prerelease, "1.2.3-alpha.2.beta", ""},
        {"1.2.3-alpha.2.beta", semver::inc::prerelease, "1.2.3-alpha.3.beta", ""},
        {"1.2.3-alpha.10.0.beta", semver::inc::prerelease, "1.2.3-alpha.10.1.beta", ""},
        {"1.2.3-alpha.10.1.beta", semver::inc::prerelease, "1.2.3-alpha.10.2.beta", ""},
        {"1.2.3-alpha.10.2.beta", semver::inc::prerelease, "1.2.3-alpha.10.3.beta", ""},
        {"1.2.3-alpha.10.beta.0", semver::inc::prerelease, "1.2.3-alpha.10.beta.1", ""},
        {"1.2.3-alpha.10.beta.1", semver::inc::prerelease, "1.2.3-alpha.10.beta.2", ""},
        {"1.2.3-alpha.10.beta.2", semver::inc::prerelease, "1.2.3-alpha.10.beta.3", ""},
        {"1.2.3-alpha.9.beta", semver::inc::prerelease, "1.2.3-alpha.10.beta", ""},
        {"1.2.3-alpha.10.beta", semver::inc::prerelease, "1.2.3-alpha.11.beta", ""},
        {"1.2.3-alpha.11.beta", semver::inc::prerelease, "1.2.3-alpha.12.beta", ""},
        {"1.2.0", semver::inc::patch, "1.2.1", ""},
        {"1.2.0-1", semver::inc::patch, "1.2.0", ""},
        {"1.2.0", semver::inc::minor, "1.3.0", ""},
        {"1.2.3-1", semver::inc::minor, "1.3.0", ""},
        {"1.2.0", semver::inc::major, "2.0.0", ""},
        {"1.2.3-1", semver::inc::major, "2.0.0", ""},

        {"1.2.4", semver::inc::prerelease, "1.2.5-dev", "dev"},
        {"1.2.3-0", semver::inc::prerelease, "1.2.3-dev", "dev"},
        {"1.2.3-alpha.0", semver::inc::prerelease, "1.2.3-dev", "dev"},
        {"1.2.3-alpha.0", semver::inc::prerelease, "1.2.3-alpha.1", "alpha"},
        {"1.2.3-alpha.0.beta", semver::inc::prerelease, "1.2.3-dev", "dev"},
        {"1.2.3-alpha.0.beta", semver::inc::prerelease, "1.2.3-alpha.1.beta", "alpha"},
        {"1.2.3-alpha.10.0.beta", semver::inc::prerelease, "1.2.3-dev", "dev"},
        {"1.2.3-alpha.10.0.beta", semver::inc::prerelease, "1.2.3-alpha.10.1.beta", "alpha"},
        {"1.2.3-alpha.10.1.beta", semver::inc::prerelease, "1.2.3-alpha.10.2.beta", "alpha"},
        {"1.2.3-alpha.10.2.beta", semver::inc::prerelease, "1.2.3-alpha.10.3.beta", "alpha"},
        {"1.2.3-alpha.10.beta.0", semver::inc::prerelease, "1.2.3-dev", "dev"},
        {"1.2.3-alpha.10.beta.0", semver::inc::prerelease, "1.2.3-alpha.10.beta.1", "alpha"},
        {"1.2.3-alpha.10.beta.1", semver::inc::prerelease, "1.2.3-alpha.10.beta.2", "alpha"},
        {"1.2.3-alpha.10.beta.2", semver::inc::prerelease, "1.2.3-alpha.10.beta.3", "alpha"},
        {"1.2.3-alpha.9.beta", semver::inc::prerelease, "1.2.3-dev", "dev"},
        {"1.2.3-alpha.9.beta", semver::inc::prerelease, "1.2.3-alpha.10.beta", "alpha"},
        {"1.2.3-alpha.10.beta", semver::inc::prerelease, "1.2.3-alpha.11.beta", "alpha"},
        {"1.2.3-alpha.11.beta", semver::inc::prerelease, "1.2.3-alpha.12.beta", "alpha"},
        {"1.2.0", semver::inc::patch, "1.2.1-dev", "dev"},
        {"1.2.0-1", semver::inc::patch, "1.2.1-dev", "dev"},
        {"1.2.0", semver::inc::minor, "1.3.0-dev", "dev"},
        {"1.2.3-1", semver::inc::minor, "1.3.0-dev", "dev"},
        {"1.2.0", semver::inc::major, "2.0.0-dev", "dev"},
        {"1.2.3-1", semver::inc::major, "2.0.0-dev", "dev"},
        {"1.2.0-1", semver::inc::minor, "1.3.0", ""},
        {"1.0.0-1", semver::inc::major, "2.0.0", ""},
        {"1.2.3-dev.beta", semver::inc::prerelease, "1.2.3-dev.beta.0", "dev"},
    }));

    REQUIRE(semver::version::parse(std::get<2>(data)) == semver::version::parse(std::get<0>(data)).increment(std::get<1>(data), std::get<3>(data)));
}