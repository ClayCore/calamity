#pragma once

#include "types.hpp"

namespace LookupTables {
    using namespace YAML::Types::Level;
    using namespace YAML::Types::Funcs;

    using ParserVariant =
        std::variant<Parser<Entity>, Parser<Vec2>, Parser<Line>, Parser<Side>, Parser<Sector>>;

    const std::unordered_map<std::string, ParserVariant> LEVEL_PARSER = {
        // KEY        // TYPE        // HASH                          // TYPE
        { "ENTITIES", Parser<Entity>(gen_hash(0), Object::entity) },
        { "VERTICES", Parser<Entity>(gen_hash(1), Object::vert) },
        { "LINES", Parser<Entity>(gen_hash(2), Object::line) },
        { "SIDES", Parser<Entity>(gen_hash(3), Object::side) },
        { "SECTORS", Parser<Entity>(gen_hash(4), Object::sector) },
    };
} // namespace LookupTables
