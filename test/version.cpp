#include <catch2/catch_all.hpp>
#include <semver/semver.hpp>

using namespace semver::literals;

TEST_CASE("Test invalid versions", "[version]") {
    REQUIRE_THROWS_AS(semver::version::parse("-1.0.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.-1.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("0.0.-1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse(""), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("", false), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0-alpha"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0-alpha.01"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("a1.0.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.a0.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.a0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("92233720368547758072.0.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("0.92233720368547758072.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("0.0.92233720368547758072"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version(1, 2, 3, ".alpha"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version(1, 2, 3, ".alpha."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version(1, 2, 3, ".alpha. "), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("v1.0.0"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("92233720368547758072", false), semver::semver_exception);

    REQUIRE_THROWS_AS(semver::version::parse("1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2.3-0123"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2.3-0123.0123"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.1.2+.123"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("+invalid"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("-invalid"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("-invalid+invalid"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("-invalid.01"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("alpha"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("        alpha.beta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("        alpha.beta.1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("alpha.1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("alpha+beta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("        alpha_beta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("alpha."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("alpha.."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("beta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha_beta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("-alpha."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha.."), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha..1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha...1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha....1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha.....1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha......1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.0.0-alpha.......1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("01.1.1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.01.1"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.1.01"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2.3.DEV"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2-SNAPSHOT"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2.31.2.3----RC-SNAPSHOT.12.09.1--..12+788"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("1.2-RC-SNAPSHOT"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("-1.0.3-gamma+b7718"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("+justmeta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("9.8.7+meta+meta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("9.8.7-whatever+meta+meta"), semver::semver_exception);
    REQUIRE_THROWS_AS(semver::version::parse("99999999999999999999999.999999999999999999.99999999999999999----RC-SNAPSHOT.12.09.1--------------------------------..12"), semver::semver_exception);
}

TEST_CASE("Test valid versions", "[version]") {
    REQUIRE_NOTHROW(semver::version::parse("0.0.4"));
    REQUIRE_NOTHROW(semver::version::parse("1.2.3"));
    REQUIRE_NOTHROW(semver::version::parse("10.20.30"));
    REQUIRE_NOTHROW(semver::version::parse("1.1.2-prerelease+meta"));
    REQUIRE_NOTHROW(semver::version::parse("1.1.2+meta"));
    REQUIRE_NOTHROW(semver::version::parse("1.1.2+meta-valid"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-beta"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha.beta"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha.beta.1"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha.1"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha0.valid"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha.0valid"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha-a.b-c-somethinglong+build.1-aef.1-its-okay"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-rc.1+build.1"));
    REQUIRE_NOTHROW(semver::version::parse("2.0.0-rc.1+build.123"));
    REQUIRE_NOTHROW(semver::version::parse("1.2.3-beta"));
    REQUIRE_NOTHROW(semver::version::parse("10.2.3-DEV-SNAPSHOT"));
    REQUIRE_NOTHROW(semver::version::parse("1.2.3-SNAPSHOT-123"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0"));
    REQUIRE_NOTHROW(semver::version::parse("2.0.0"));
    REQUIRE_NOTHROW(semver::version::parse("1.1.7"));
    REQUIRE_NOTHROW(semver::version::parse("2.0.0+build.1848"));
    REQUIRE_NOTHROW(semver::version::parse("2.0.1-alpha.1227"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-alpha+beta"));
    REQUIRE_NOTHROW(semver::version::parse("1.2.3----RC-SNAPSHOT.12.9.1--.12+788"));
    REQUIRE_NOTHROW(semver::version::parse("1.2.3----R-S.12.9.1--.12+meta"));
    REQUIRE_NOTHROW(semver::version::parse("1.2.3----RC-SNAPSHOT.12.9.1--.12"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0+0.build.1-rc.10000aaa-kk-0.1"));
    REQUIRE_NOTHROW(semver::version::parse("1.0.0-0A.is.legal"));

    REQUIRE_NOTHROW(semver::version::parse("0.0.0"));
    REQUIRE_NOTHROW(semver::version::parse("v1.0.0", false));
    REQUIRE_NOTHROW(semver::version::parse("1.0", false));
    REQUIRE_NOTHROW(semver::version::parse("v1", false));
    REQUIRE_NOTHROW(semver::version::parse("1", false));
}

TEST_CASE("Test version strings", "[version]") {
    REQUIRE(semver::version::parse("1.2.3").str() == "1.2.3");
    REQUIRE(semver::version::parse("1.2.3-alpha.b.3").str() == "1.2.3-alpha.b.3");
    REQUIRE(semver::version::parse("1.2.3-alpha+build").str() == "1.2.3-alpha+build");
    REQUIRE(semver::version::parse("1.2.3+build").str() == "1.2.3+build");
    REQUIRE(semver::version::parse("v1.2.3", false).str() == "1.2.3");
    REQUIRE(semver::version::parse("v1", false).str() == "1.0.0");
    REQUIRE(semver::version::parse("1", false).str() == "1.0.0");
    REQUIRE(semver::version::parse("1.2", false).str() == "1.2.0");
    REQUIRE(semver::version::parse("v1.2", false).str() == "1.2.0");
    REQUIRE(semver::version::parse("18446744073709551615.18446744073709551614.18446744073709551613").str() == "18446744073709551615.18446744073709551614.18446744073709551613");

    REQUIRE(semver::version::parse("v1.2.3-alpha+build", false).str() == "1.2.3-alpha+build");
    REQUIRE(semver::version::parse("v1-alpha+build", false).str() == "1.0.0-alpha+build");
    REQUIRE(semver::version::parse("1-alpha+build", false).str() == "1.0.0-alpha+build");
    REQUIRE(semver::version::parse("1.2-alpha+build", false).str() == "1.2.0-alpha+build");
    REQUIRE(semver::version::parse("v1.2-alpha+build", false).str() == "1.2.0-alpha+build");
}

TEST_CASE("Test version components", "[version]") {
    semver::version ver = semver::version::parse("1.2.3-alpha.b.3+build");
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease() == "alpha.b.3");
    REQUIRE(ver.build_meta() == "build");
    REQUIRE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test version components, only numbers", "[version]") {
    semver::version ver = semver::version::parse("1.2.3");
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta().empty());
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE(ver.is_stable());
}

TEST_CASE("Test version components, only numbers, leading zero", "[version]") {
    semver::version ver = semver::version::parse("0.2.3");
    REQUIRE(ver.major() == 0);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta().empty());
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test version components, only built meta", "[version]") {
    semver::version ver = semver::version::parse("1.2.3+build");
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta() == "build");
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE(ver.is_stable());
}

TEST_CASE("Test version components, user-defined literal", "[version]") {
    semver::version ver = "1.2.3-alpha+build"_v;
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease() == "alpha");
    REQUIRE(ver.build_meta() == "build");
    REQUIRE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test version components, user-defined loose literal", "[version]") {
    semver::version ver = "v1.2-alpha+build"_lv;
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 0);
    REQUIRE(ver.prerelease() == "alpha");
    REQUIRE(ver.build_meta() == "build");
    REQUIRE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test default version", "[version]") {
    semver::version ver = semver::version();
    REQUIRE(ver.major() == 0);
    REQUIRE(ver.minor() == 0);
    REQUIRE(ver.patch() == 0);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta().empty());
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test version construction, only major", "[version]") {
    semver::version ver = semver::version(1);
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 0);
    REQUIRE(ver.patch() == 0);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta().empty());
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE(ver.is_stable());
}

TEST_CASE("Test version construction, only major & minor", "[version]") {
    semver::version ver = semver::version(1, 2);
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 0);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta().empty());
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE(ver.is_stable());
}

TEST_CASE("Test version construction, major & minor & patch", "[version]") {
    semver::version ver = semver::version(1, 2, 3);
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease().empty());
    REQUIRE(ver.build_meta().empty());
    REQUIRE_FALSE(ver.is_prerelease());
    REQUIRE(ver.is_stable());
}

TEST_CASE("Test version construction, major & minor & patch & prerelease", "[version]") {
    semver::version ver = semver::version(1, 2, 3, "alpha");
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease() == "alpha");
    REQUIRE(ver.build_meta().empty());
    REQUIRE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test version construction, major & minor & patch & prerelease & build", "[version]") {
    semver::version ver = semver::version(1, 2, 3, "alpha", "build");
    REQUIRE(ver.major() == 1);
    REQUIRE(ver.minor() == 2);
    REQUIRE(ver.patch() == 3);
    REQUIRE(ver.prerelease() == "alpha");
    REQUIRE(ver.build_meta() == "build");
    REQUIRE(ver.is_prerelease());
    REQUIRE_FALSE(ver.is_stable());
}

TEST_CASE("Test version without suffixes", "[version]") {
    semver::version ver = semver::version(1, 2, 3, "alpha", "build");
    semver::version ws = ver.without_suffixes();
    REQUIRE(ws.major() == 1);
    REQUIRE(ws.minor() == 2);
    REQUIRE(ws.patch() == 3);
    REQUIRE(ws.prerelease().empty());
    REQUIRE(ws.build_meta().empty());
    REQUIRE_FALSE(ws.is_prerelease());
    REQUIRE(ws.is_stable());
}