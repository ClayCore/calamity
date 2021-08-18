#pragma once

#include "zcommon.hpp"

namespace Calamity::File
{
    std::optional<std::vector<std::string>>
    load_file(std::string file_path);
} // namespace Calamity::File
