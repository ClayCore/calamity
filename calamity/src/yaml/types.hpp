#pragma once

#include "zcommon.hpp"

namespace YAML::Types {
    // Utility types for level structures
    namespace Level {

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

        enum class LevelObject {
            Entity,
            Vertex,
            Line,
            Side,
            Sector,
        };
    } // namespace Level

    // ===============================================
    // Utility types for passing arguments to functors
    // ===============================================
    struct FuncArgs {
        // Unparsed data
        std::vector<std::string> data;

        // Starting index from which we read
        // the file
        usize index;
    };

    // ==========================================
    // = Parser functors with specialization ====
    // ==========================================
    template <class T>
    auto parse_functor(const FuncArgs& args) -> void;

    // TODO: Make all parsing functions and move them to a source file
    template <>
    auto parse_functor<Level::Entity>(const FuncArgs& args) -> void;

    template <>
    auto parse_functor<Level::Vec2>(const FuncArgs& args) -> void;

    template <>
    auto parse_functor<Level::Line>(const FuncArgs& args) -> void;

    template <>
    auto parse_functor<Level::Side>(const FuncArgs& args) -> void;

    template <>
    auto parse_functor<Level::Sector>(const FuncArgs& args) -> void;

} // namespace YAML::Types
