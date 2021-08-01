#pragma once

#include "zcommon.hpp"

constexpr auto Z_HashStr(std::string_view str) noexcept -> u32 {
    // Magic prime
    u32   hash = 5381;
    usize len  = str.length();

    for (const char* c = str.data(); c < str.data() + len; ++c) {
        hash = ((hash << 5) + hash) + u8(*c);
    }

    return hash;
}
