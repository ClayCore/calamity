#pragma once

#include "zcommon.hpp"

namespace File
{
    std::optional<std::vector<std::string>>
    load_file(std::string file_path);
} // namespace File
