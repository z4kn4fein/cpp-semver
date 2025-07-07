#include <iostream>
#include "semver/semver.hpp"

using namespace std;
using namespace semver::literals;

int main() {
    semver::version version = "1.2.3-alpha.1+build"_v;
    cout << "version: " << version << endl << endl;

    cout << "==============================" << endl;
    cout << "Details" << endl;
    cout << "==============================" << endl;
    cout << "major: " << version.major() << endl;
    cout << "minor: " << version.minor() << endl;
    cout << "patch: " << version.patch() << endl;
    cout << "pre-release: " << version.prerelease() << endl;
    cout << "buildmeta: " << version.build_meta() << endl;
    cout << "without suffixes: " << version.without_suffixes() << endl;
    cout << "is prerelease? " << version.is_prerelease() << endl;
    cout << "is stable? " << version.is_stable() << endl << endl;
    
    cout << "==============================" << endl;
    cout << "Increment" << endl;
    cout << "==============================" << endl;
    cout << "next major: " << version.next_major() << endl;
    cout << "next minor: " << version.next_minor() << endl;
    cout << "next patch: " << version.next_patch() << endl;
    cout << "next pre-release: " << version.next_prerelease() << endl;
    cout << "next major with pre-release: " << version.next_major("beta") << endl << endl;

    cout << "==============================" << endl;
    cout << "Compare" << endl;
    cout << "==============================" << endl;
    cout << "version < 1.2.3 = " << (version < "1.2.3"_v) << endl;
    cout << "version > 1.2.2 = " << (version > "1.2.2"_v) << endl;
    cout << "version < 1.2.3-alpha.2 = " << (version < "1.2.3-alpha.2"_v) << endl;
    cout << "version > 1.2.3-alpha = " << (version > "1.2.3-alpha"_v) << endl;
    cout << "version == 1.2.3-alpha.1 = " << (version == "1.2.3-alpha.1"_v) << endl;
    cout << "version <= 1.2.3-alpha.1 = " << (version == "1.2.3-alpha.1"_v) << endl;
    cout << "version < 1.2.3-beta = " << (version < "1.2.3-beta"_v) << endl << endl;
    
    cout << "==============================" << endl;
    cout << "Loose version" << endl;
    cout << "==============================" << endl;
    cout << "v1 = " << "v1"_lv << endl;
    cout << "1.2 = " << "1.2"_lv << endl;
    cout << "1-alpha = " << "1.0-alpha"_lv << endl;
}