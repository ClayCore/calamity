#pragma once

#include "zcommon.hpp"

namespace File {
    auto load_file(std::string file_path) -> std::optional<std::vector<std::string>>;
} // namespace File