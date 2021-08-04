#pragma once

#include "types.hpp"

namespace YAML::LUTs {
    using namespace Types::Level;

    // ============================
    // = Map tags lookup table ====
    // ============================

    // Used for parsing different types of level objects from map files
    constexpr const usize NUM_MAP_TAGS = 5;

    const std::array<std::shared_ptr<MapObject>, NUM_MAP_TAGS> MAP_OBJECTS = {
        std::make_shared<Entity>(), std::make_shared<Vec2>(),   std::make_shared<Line>(),
        std::make_shared<Side>(),   std::make_shared<Sector>(),
    };
} // namespace YAML::LUTs
