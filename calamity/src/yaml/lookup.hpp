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

    // Forgive me god for I have sinned...
    using LambdaEnt    = std::function<std::vector<Entity>(const FuncArgs&)>;
    using LambdaVert   = std::function<std::vector<Vec2>(const FuncArgs&)>;
    using LambdaLine   = std::function<std::vector<Line>(const FuncArgs&)>;
    using LambdaSide   = std::function<std::vector<Side>(const FuncArgs&)>;
    using LambdaSector = std::function<std::vector<Sector>(const FuncArgs&)>;

    // Used for parsing different types of level objects from map files
    static std::map<std::string, std::any> PARSER_FUNCTORS = {
        { "PARSE_ENTS",
          std::make_any<LambdaEnt>([](const FuncArgs& args) { return Types::parse_functor<Entity>(args); }) },
        { "PARSE_VERTS",
          std::make_any<LambdaVert>([](const FuncArgs& args) { return Types::parse_functor<Vec2>(args); }) },
        { "PARSE_LINES",
          std::make_any<LambdaLine>([](const FuncArgs& args) { return Types::parse_functor<Line>(args); }) },
        { "PARSE_SIDES",
          std::make_any<LambdaSide>([](const FuncArgs& args) { return Types::parse_functor<Side>(args); }) },
        { "PARSE_SECTORS",
          std::make_any<LambdaSector>([](const FuncArgs& args) { return Types::parse_functor<Sector>(args); }) },
    };
} // namespace YAML::LUTs
