#pragma once

#include "types.hpp"

namespace YAML::LUTs {
    using Types::FuncArgs;
    using Types::Level::Entity;
    using Types::Level::Line;
    using Types::Level::Sector;
    using Types::Level::Side;
    using Types::Level::Vec2;

    // ===========================
    // = Functor lookup table ====
    // ===========================

    // Used for parsing different types of level objects from map files
    static std::map<std::string, std::any> PARSER_FUNCTORS = {
        { "PARSE_ENTS", [](const FuncArgs& args) { return Types::parse_functor<Entity>(args); } },
        { "PARSE_VERTS", [](const FuncArgs& args) { return Types::parse_functor<Vec2>(args); } },
        { "PARSE_LINES", [](const FuncArgs& args) { return Types::parse_functor<Line>(args); } },
        { "PARSE_SIDES", [](const FuncArgs& args) { return Types::parse_functor<Side>(args); } },
        { "PARSE_SECTORS", [](const FuncArgs& args) { return Types::parse_functor<Sector>(args); } },
    };
} // namespace YAML::LUTs
