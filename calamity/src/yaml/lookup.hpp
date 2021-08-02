#pragma once

#include "types.hpp"

namespace YAML::LUTs {
    using namespace Types;
    using Functor = std::function<void(const FuncArgs& args)>;
    
    // ===========================
    // = Functor lookup table ====
    // ===========================

    // Used for parsing different types of level objects from map files
    static std::map<std::string, Functor> PARSER_FUNCTORS = {
        { "PARSE_ENTS", [](const FuncArgs& args) { return parse_functor<Level::Entity>(args); } },
        { "PARSE_VERTS", [](const FuncArgs& args) { return parse_functor<Level::Vec2>(args); } },
        { "PARSE_LINES", [](const FuncArgs& args) { return parse_functor<Level::Line>(args); } },
        { "PARSE_SIDES", [](const FuncArgs& args) { return parse_functor<Level::Side>(args); } },
        { "PARSE_SECTORS", [](const FuncArgs& args) { return parse_functor<Level::Sector>(args); } },
    };
} // namespace YAML::LUTs
