#pragma once

#include "zcommon.hpp"

namespace Detail {
    constexpr auto fnv1a_32(char const* s, usize count) -> u32 {
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
    }
} // namespace Detail

constexpr auto operator"" _hash(char const* s, usize count) -> u32 {
    return Detail::fnv1a_32(s, count);
}

constexpr auto get_hash(const std::string& key) -> u32 {
    return Detail::fnv1a_32(key.c_str(), key.size());
}
