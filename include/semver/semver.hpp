/*
License: MIT (http://opensource.org/licenses/MIT).

Copyright (c) 2022 Peter Csajtai <peter.csajtai@outlook.com>

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

#ifndef Z4KN4FEIN_SEMVER_H
#define Z4KN4FEIN_SEMVER_H

#include <string>
#include <regex>
#include <vector>

namespace semver
{

    using build_identifier_part = uint64_t;

    const std::string default_prerelease_part = "0";
    const char prerelease_delimiter = '.';
    const std::string numbers = "0123456789";
    const std::string prerelease_allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-";
    const std::string version_pattern = "^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)"
                                        "(?:-((?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\\.(?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*))*))"
                                        "?(?:\\+([0-9a-zA-Z-]+(?:\\.[0-9a-zA-Z-]+)*))?$";
    const std::string loose_version_pattern = "^v?(0|[1-9]\\d*)(?:\\.(0|[1-9]\\d*))?(?:\\.(0|[1-9]\\d*))"
                                              "?(?:-((?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\\.(?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*))*))"
                                              "?(?:\\+([0-9a-zA-Z-]+(?:\\.[0-9a-zA-Z-]+)*))?$";

    struct semver_exception : public std::runtime_error {
        semver_exception(const std::string& message) : std::runtime_error(message) { }
    };

    inline build_identifier_part parse_build_identifier_part(const std::string& version_part)
    {
        return static_cast<build_identifier_part>(std::stoull(version_part));
    }

    inline std::vector<std::string> split(const std::string& text, const char& delimiter) {
        std::size_t pos_start = 0, pos_end, delim_len = 1;
        std::string current;
        std::vector<std::string> result;

        while ((pos_end = text.find(delimiter, pos_start)) != std::string::npos) {
            current = text.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            result.push_back(current);
        }

        result.push_back(text.substr(pos_start));
        return result;
    }

    inline bool is_numeric(const std::string& text) {
        return text.find_first_not_of(numbers) == std::string::npos;
    }

    inline bool is_valid_prerelease(const std::string& text) {
        return text.find_first_not_of(numbers + prerelease_allowed_chars) == std::string::npos;
    }

    class prerelease_part {
    private:
        bool m_numeric = false;
        std::string m_value;
        build_identifier_part m_numeric_value;
    public:
        prerelease_part(const std::string& part) {
            if (part.empty()) {
                throw semver_exception("Pre-release identity contains an empty part.");
            }

            if (is_numeric(part)) {
                if (part.size() > 1 && part[0] == '0') {
                    throw semver_exception(
                            "Pre-release part '" + part + "' is numeric but contains a leading zero.");
                }
                m_numeric_value = parse_build_identifier_part(part);
                m_numeric = true;
            }
            if (!is_valid_prerelease(part)) {
                throw semver_exception(
                        "Pre-release part '" + part + "' contains an invalid character.");
            }
            m_value = part;
        }

        bool numeric() const { return m_numeric; }
        std::string value() const { return m_value; }
        build_identifier_part numeric_value() const { return m_numeric_value; }

        int compare(const prerelease_part& other) const {
            if (m_numeric && !other.m_numeric) return -1;
            if (!m_numeric && other.m_numeric) return 1;
            if (m_numeric && other.m_numeric) {
                return (m_numeric_value < other.m_numeric_value) ? -1 : (m_numeric_value > other.m_numeric_value);
            }
            return (m_value < other.m_value) ? -1 : (m_value > other.m_value);
        }
    };

    class prerelease_descriptor {
    private:
        std::vector<prerelease_part> m_parts;
        std::string prerelease_str;

        prerelease_descriptor(const std::vector<prerelease_part>& parts)
                : m_parts(parts) {
            if (parts.empty()) prerelease_str = "";
            for (const auto &part : parts) {
                if (!prerelease_str.empty()) prerelease_str += prerelease_delimiter;
                prerelease_str += part.value();
            }
        }
    public:
        std::string str() const { return prerelease_str; }
        bool is_empty() const { return m_parts.empty(); }

        std::string identity() const {
            if (is_empty()) return "";
            return m_parts.front().value();
        }

        prerelease_descriptor increment() const {
            std::vector<prerelease_part> new_parts = (m_parts);
            int last_numeric_index = -1;
            for (int i = 0; i < new_parts.size(); ++i) {
                if (new_parts[i].numeric()) last_numeric_index = i;
            }
            if (last_numeric_index != -1) {
                prerelease_part last = new_parts[last_numeric_index];
                new_parts[last_numeric_index] = prerelease_part(std::to_string(last.numeric_value() + 1));
            } else {
                new_parts.push_back(prerelease_part(default_prerelease_part));
            }
            return prerelease_descriptor(new_parts);
        }

        int compare(const prerelease_descriptor& other) const {
            auto this_size = m_parts.size();
            auto other_size = other.m_parts.size();

            auto count = std::min(this_size, other_size);
            for (int i = 0; i < count; ++i) {
                int cmp = m_parts[i].compare(other.m_parts[i]);
                if (cmp != 0) return cmp;
            }
            return (this_size < other_size) ? -1 : (this_size > other_size);
        }

        bool operator<(const prerelease_descriptor& other) const {
            return compare(other) == -1;
        }

        bool operator>(const prerelease_descriptor& other) const {
            return (other < *this);
        }

        bool operator==(const prerelease_descriptor& other) const {
            return prerelease_str == other.prerelease_str;
        }

        bool operator!=(const prerelease_descriptor& other) const {
            return prerelease_str != other.prerelease_str;
        }

        static prerelease_descriptor parse(const std::string& prerelease_part_str) {
            if (prerelease_part_str.empty()) return empty();
            std::vector<prerelease_part> prerelease_parts;
            std::vector<std::string> parts = split(prerelease_part_str, prerelease_delimiter);
            for(auto& part : parts) {
                prerelease_parts.push_back(prerelease_part(part));
            }
            return prerelease_descriptor(prerelease_parts);
        }

        static prerelease_descriptor empty() {
            return prerelease_descriptor({});
        }

        static prerelease_descriptor initial() {
            return prerelease_descriptor::parse(default_prerelease_part);
        }
    };

    enum inc { major, minor, patch, prerelease };

    class version {
    private:
        build_identifier_part m_major;
        build_identifier_part m_minor;
        build_identifier_part m_patch;
        prerelease_descriptor m_prerelease;
        std::string m_build_meta;

        int compare(const version& other) const {
            if (m_major > other.m_major) return 1;
            if (m_major < other.m_major) return -1;
            if (m_minor > other.m_minor) return 1;
            if (m_minor < other.m_minor) return -1;
            if (m_patch > other.m_patch) return 1;
            if (m_patch < other.m_patch) return -1;
            if (!m_prerelease.is_empty() && other.m_prerelease.is_empty()) return -1;
            if (m_prerelease.is_empty() && !other.m_prerelease.is_empty()) return 1;
            if (!m_prerelease.is_empty() && !other.m_prerelease.is_empty()) return m_prerelease.compare(other.m_prerelease);
            return 0;
        }
    public:
        version(build_identifier_part major = 0,
                build_identifier_part minor = 0,
                build_identifier_part patch = 0,
                std::string prerelease = "",
                std::string build_meta = "")
                : m_major{major},
                  m_minor{minor},
                  m_patch{patch},
                  m_prerelease{prerelease_descriptor::parse(prerelease)},
                  m_build_meta{build_meta} { }

        build_identifier_part major() const { return m_major; }
        build_identifier_part minor() const { return m_minor; }
        build_identifier_part patch() const { return m_patch; }
        std::string prerelease() const { return m_prerelease.str(); }
        std::string build_meta() const { return m_build_meta; }

        bool is_prerelease() const { return !m_prerelease.is_empty(); }
        bool is_stable() const { return m_major > 0 && m_prerelease.is_empty(); }

        std::string str() const {
            std::string result = std::to_string(m_major) + "." + std::to_string(m_minor) + "." + std::to_string(m_patch);
            if (!m_prerelease.is_empty()) result += "-" + m_prerelease.str();
            if (!m_build_meta.empty()) result += "+" + m_build_meta;
            return result;
        }

        version without_suffixes() const {
            return version(m_major, m_minor, m_patch);
        }

        version next_major(const std::string& prerelease = "") const {
            return version(m_major + 1, 0, 0, prerelease);
        }

        version next_minor(const std::string& prerelease = "") const {
            return version(m_major, m_minor + 1, 0, prerelease);
        }

        version next_patch(const std::string& prerelease = "") const {
            return version(m_major, m_minor, (!is_prerelease() || !prerelease.empty() ? m_patch + 1 : m_patch), prerelease);
        }

        version next_prerelease(const std::string& prerelease = "") const {
            std::string pre = default_prerelease_part;
            if (!prerelease.empty()) {
                pre = is_prerelease() && m_prerelease.identity() == prerelease ? m_prerelease.increment().str() : prerelease;
            } else if (prerelease.empty() && is_prerelease()) {
                pre = m_prerelease.increment().str();
            }
            return version(m_major, m_minor, is_prerelease() ? m_patch : m_patch + 1, pre);
        }

        version increment(inc by, const std::string& prerelease = "") const {
            switch (by) {
                case semver::major: return next_major(prerelease);
                case semver::minor: return next_minor(prerelease);
                case semver::patch: return next_patch(prerelease);
                case semver::prerelease: return next_prerelease(prerelease);
                default: throw semver_exception("Invalid 'by' parameter in 'increment()' function.");
            }
        }

        bool operator<(const version& other) const {
            return compare(other) == -1;
        }

        bool operator<=(const version& other) const {
            return compare(other) <= 0;
        }

        bool operator>(const version& other) const {
            return compare(other) == 1;
        }

        bool operator>=(const version& other) const {
            return compare(other) >= 0;
        }

        bool operator==(const version& other) const {
            return compare(other) == 0;
        }

        bool operator!=(const version& other) const {
            return compare(other) != 0;
        }

        static version parse(const std::string& version_str, bool strict = true) {
            std::regex regex(strict ? version_pattern : loose_version_pattern);
            std::cmatch match;
            build_identifier_part major;
            build_identifier_part minor;
            build_identifier_part patch;
            std::string prerelease = "";
            std::string build_meta = "";

            if (!std::regex_match(version_str.c_str(), match, regex)) {
                throw semver_exception("Invalid version: " + version_str);
            }

            auto major_m = match[1];
            auto minor_m = match[2];
            auto patch_m = match[3];
            auto prerelease_m = match[4];
            auto build_meta_m = match[5];

            if (prerelease_m.matched) prerelease = prerelease_m.str();
            if (build_meta_m.matched) build_meta = build_meta_m.str();

            try {
                if (strict && major_m.matched && minor_m.matched && patch_m.matched) {
                    major = parse_build_identifier_part(major_m);
                    minor = parse_build_identifier_part(minor_m);
                    patch = parse_build_identifier_part(patch_m);
                } else if (!strict && major_m.matched) {
                    major = parse_build_identifier_part(major_m);
                    minor = minor_m.matched ? parse_build_identifier_part(minor_m) : 0;
                    patch = patch_m.matched ? parse_build_identifier_part(patch_m) : 0;
                } else {
                    throw semver_exception("Invalid version: " + version_str);
                }

                return version(major, minor, patch, prerelease, build_meta);
            } catch (std::exception& exception) {
                throw semver_exception("Version parse error: " + std::string(exception.what()));
            }
        }
    };

    inline std::ostream & operator<<(std::ostream& str, const version& version) {
        for (const auto s : version.str()) str.put(s);
        return str;
    }

    namespace literals
    {
        inline version operator""_v(const char* text, std::size_t length) {
            return version::parse(std::string(text, length));
        }

        inline version operator""_lv(const char* text, std::size_t length) {
            return version::parse(std::string(text, length), false);
        }
    }
}

#endif // Z4KN4FEIN_SEMVER_H