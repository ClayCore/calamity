#pragma once

#include "zcommon.hpp"

// TODO: Move to a separate type utils file
// ====================
// = Utility types ====
// ====================

namespace Types {
    struct Vec2 {
        double x;
        double y;
    };

    struct Entity {
        Vec2 pos;
        u16  angle;
        u16  type;
    };

    struct Line {
        u16 start;
        u16 end;
    };

    struct Side {
        u16 sector_index;
    };

    struct Sector {
        i16 floor_height;
        i16 ceiling_height;

        std::string floor_texture;
        std::string ceiling_texture;

        u8 light_level;
    };

    struct LevelData {
        std::vector<Entity> entities;
        std::vector<Vec2>   vertices;
        std::vector<Line>   lines;
        std::vector<Side>   sides;
        std::vector<Sector> sectors;
    };

    // Conglomerate type for dealing with all lookups
    template <typename T> struct ParseObject {
        using RetVal  = std::vector<T>;
        using Functor = std::function<RetVal(const std::vector<std::string>&, usize)>;

        u64     m_hash;
        Functor m_functor;

        ParseObject(u64 hash, Functor functor) {
            this->m_hash    = hash;
            this->m_functor = functor;
        }

        auto get_hash() -> u64 {
            return this->m_hash;
        }

        auto get_func() -> Functor {
            return this->m_functor;
        }
    };

} // namespace Types

// ========================
// = Utility functions ====
// ========================
namespace Funcs {
    using namespace Types;

    std::vector<Entity> parse_ents(const std::vector<std::string>& data, usize index) {
        std::vector<Entity> result;
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                break;
            }

            std::cout << "Ent: \"" << data[i] << "\"" << std::endl;
        }
        return result;
    }

    std::vector<Vec2> parse_verts(const std::vector<std::string>& data, usize index) {
        std::vector<Vec2> result;
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                break;
            }

            std::cout << "Vert: \"" << data[i] << "\"" << std::endl;
        }
        return result;
    }

    std::vector<Line> parse_lines(const std::vector<std::string>& data, usize index) {
        std::vector<Line> result;
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                break;
            }

            std::cout << "Line: \"" << data[i] << "\"" << std::endl;
        }
        return result;
    }

    std::vector<Side> parse_sides(const std::vector<std::string>& data, usize index) {
        std::vector<Side> result;
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                break;
            }

            std::cout << "Side: \"" << data[i] << "\"" << std::endl;
        }
        return result;
    }

    std::vector<Sector> parse_sectors(const std::vector<std::string>& data, usize index) {
        std::vector<Sector> result;
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                break;
            }

            std::cout << "Sector: \"" << data[i] << "\"" << std::endl;
        }
        return result;
    }
} // namespace Funcs

namespace Tables {
    using namespace Types;
    using namespace Funcs;

    constexpr auto gen_hash(usize key) noexcept -> const u64 {
        switch (key) {
            // ENTITIES
            case 0: {
                return std::hash<std::string>()("ents:");
                break;
            }
            // VERTICES
            case 1: {
                return std::hash<std::string>()("verts:");
                break;
            }
            // LINES
            case 2: {
                return std::hash<std::string>()("lines:");
                break;
            }
            // SIDES
            case 3: {
                return std::hash<std::string>()("sides:");
                break;
            }
            // SECTORS
            case 4: {
                return std::hash<std::string>()("sectors:");
                break;
            }
            default: {
                return 0;
            }
        }
    };

    using ParseVariant = std::variant<ParseObject<Entity>, ParseObject<Vec2>, ParseObject<Line>,
                                      ParseObject<Side>, ParseObject<Sector>>;

    const std::unordered_map<std::string, ParseVariant> PARSING_ACTIONS = {
        // Id key     Type                Hash         Parsing functor
        { "ENTITIES", ParseObject<Entity>(gen_hash(0), parse_ents) },
        { "VERTICES", ParseObject<Vec2>(gen_hash(1), parse_verts) },
        { "LINES", ParseObject<Line>(gen_hash(2), parse_lines) },
        { "SIDES", ParseObject<Side>(gen_hash(3), parse_sides) },
        { "SECTORS", ParseObject<Sector>(gen_hash(4), parse_sectors) },
    };
} // namespace Tables
