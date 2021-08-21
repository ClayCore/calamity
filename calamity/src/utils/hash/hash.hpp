#pragma once

#include "zcommon.hpp"
namespace Calamity
{
    namespace Detail
    {
        [[nodiscard]] constexpr u32 fnv1a_32(char const* s, usize count) noexcept
        {
            return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
        }
    }  // namespace Detail

    [[nodiscard]] constexpr u32 operator"" _hash(char const* s, usize count) noexcept
    {
        return Detail::fnv1a_32(s, count);
    }

    [[nodiscard]] u32 H_GetHash(const std::string& key) noexcept
    {
        return Detail::fnv1a_32(key.c_str(), key.size());
    }
}  // namespace Calamity
