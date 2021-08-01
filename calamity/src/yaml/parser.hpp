#pragma once

#include "zcommon.hpp"

namespace YAML {
    auto parse_ents(std::vector<std::string>&& data, usize index) -> void;
    auto parse_verts(std::vector<std::string>&& data, usize index) -> void;
    auto parse_lines(std::vector<std::string>&& data, usize index) -> void;
    auto parse_sides(std::vector<std::string>&& data, usize index) -> void;
    auto parse_sectors(std::vector<std::string>&& data, usize index) -> void;

    auto parse(const std::vector<std::string>& data) -> void;
} // namespace YAML
