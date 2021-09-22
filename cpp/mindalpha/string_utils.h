//
// Copyright 2021 Mobvista
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#pragma once

#include <stdint.h>
#include <string>
#include <string_view>
#include <algorithm>
#include <boost/container/small_vector.hpp>

//
// ``string_utils.h`` defines utility functions and classes for strings
// which are mainly used in the implementation of ``CombineSchema`` and
// ``IndexBatch``.
//

namespace mindalpha
{

inline uint64_t BKDRHash(const char* str, size_t len, uint64_t seed)
{
    for (size_t i = 0; i < len; i++)
        seed = seed * 131 + str[i];
    return seed;
}

inline uint64_t BKDRHash(std::string_view str)
{
    return BKDRHash(str.data(), str.size(), 0);
}

inline uint64_t BKDRHashWithEqualPostfix(const char* str, size_t len, uint64_t seed)
{
    seed = BKDRHash(str, len, seed);
    seed = seed * 131 + '=';
    return seed;
}

inline uint64_t BKDRHashWithEqualPostfix(std::string_view str)
{
    return BKDRHashWithEqualPostfix(str.data(), str.size(), 0);
}

inline uint64_t BKDRHashWithSeparatePrefixAndEqualPostfix(const char* str, size_t len, uint64_t seed)
{
    seed = seed * 131 + '\001';
    seed = BKDRHash(str, len, seed);
    seed = seed * 131 + '=';
    return seed;
}

constexpr uint64_t CombineHashCodes(uint64_t h, uint64_t x)
{
    return h ^ (x + 0x9e3779b9 + (h << 6) + (h >> 2));
}

struct StringViewHash
{
    std::string_view view_;
    uint64_t hash_;

    StringViewHash() : hash_(0) { }
    StringViewHash(std::string_view view, uint64_t hash) : view_(view), hash_(hash) { }
    StringViewHash(uint64_t hash) : hash_(hash) { }
    StringViewHash(const char* str, size_t len) : view_(str, len), hash_(BKDRHash(str, len, 0)) { }
    StringViewHash(const std::string& str) : view_(str), hash_(BKDRHash(view_.data(), view_.size(), 0)) { }
    StringViewHash(std::string_view view) : view_(view), hash_(BKDRHash(view_.data(), view_.size(), 0)) { }
};

using StringViewVector = boost::container::small_vector<std::string_view, 2>;
using StringViewHashVector = boost::container::small_vector<StringViewHash, 1>;

inline StringViewVector SplitStringView(std::string_view str, std::string_view delims)
{
    StringViewVector output;
    for (auto first = str.data(), second = str.data(), last = first + str.size();
        second != last && first != last;
        first = second + 1)
    {
        second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));
        if (first != second)
            output.emplace_back(first, second - first);
    }
    return output;
}

inline StringViewVector SplitStringView(std::string_view str)
{
    using namespace std::string_view_literals;
    return SplitStringView(std::move(str), " "sv);
}

inline StringViewHashVector
SplitFilterStringViewHash(std::string_view str, std::string_view delims, std::string_view filter)
{
    StringViewHashVector output;
    for (auto first = str.data(), second = str.data(), last = first + str.size();
        second != last && first != last;
        first = second + 1)
    {
        second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));
        if (first != second)
        {
            std::string_view view(first, second - first);
            if (view != filter)
                output.emplace_back(view);
        }
    }
    return output;
}

inline StringViewHashVector SplitFilterStringViewHash(std::string_view str, std::string_view delims)
{
    using namespace std::string_view_literals;
    return SplitFilterStringViewHash(str, delims, "none"sv);
}

inline StringViewHashVector SplitFilterStringViewHash(std::string_view str)
{
    using namespace std::string_view_literals;
    return SplitFilterStringViewHash(str, " "sv);
}

inline char FormatHexDigit(int d)
{
    if (d >= 10)
        return 'a' + (d - 10);
    else
        return '0' + d;
}

inline std::string FormatChar(char ch, char delimiter = '\'')
{
    switch (ch)
    {
        case '\0': return "\\0";
        case '\a': return "\\a";
        case '\b': return "\\b";
        case '\t': return "\\t";
        case '\n': return "\\n";
        case '\v': return "\\v";
        case '\f': return "\\f";
        case '\r': return "\\r";
        case '\'': return delimiter == '\'' ? "\\'" : "'";
        case '"': return delimiter == '"' ? "\\\"" : "\"";
        case '\\': return "\\\\";
        default:
            std::string str;
            const int c = static_cast<unsigned char>(ch);
            if (0x20 <= c && c <= 0x7E)
                str.push_back(ch);
            else
            {
                str.push_back('\\');
                str.append("u00");
                str.push_back(FormatHexDigit((c >> 8) & 0xF));
                str.push_back(FormatHexDigit(c & 0xF));
            }
            return str;
    }
}

inline std::string ToSource(char ch, char delimiter = '\'')
{
    std::string sout;
    sout.push_back(delimiter);
    sout.append(FormatChar(ch, delimiter));
    sout.push_back(delimiter);
    return sout;
}

inline std::string ToSource(std::string_view str, char delimiter = '"')
{
    std::string sout;
    sout.push_back(delimiter);
    for (char ch : str)
        sout.append(FormatChar(ch, delimiter));
    sout.push_back(delimiter);
    return sout;
}

inline bool EndsWith(std::string_view str, std::string_view sub)
{
    const size_t i = str.size() - sub.size();
    return str.size() >= sub.size() && str.compare(i, sub.size(), sub) == 0;
}

}
