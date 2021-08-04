#pragma once

#include "zcommon.hpp"

namespace YAML::Types {
    // ===========================
    // = Utility types        ====
    // = for level structures ====
    // ===========================
    namespace Level {
        // Used for passing arguments
        // to specific parsing functions
        // without repeating code too much
        struct ParseFuncArgs {
            // Processed config file.
            const std::vector<std::string>& data;

            // Offset from the start of the file.
            usize offset;
        };

        // Virtual class that gets derived
        // by every map object, for parsing
        // and deserializing.
        template <class Tag>
        class MapObject {
          public:
            // Parse a single line from the config file.
            virtual auto parse_line(const std::string& key, const std::string& val) -> Tag {
                Tag result = {};

                return result;
            }

            // Parse an entire object, this is what actually gets called.
            auto parse_object(const ParseFuncArgs& args) -> std::vector<Tag> {
                std::vector<Tag> result = {};
                Tag              object = {};

                for (auto it = args.data.begin() + args.offset; it < args.data.end(); ++it) {
                    std::string line = *it;

                    // End of parsing block
                    // for the specific object
                    if (line == "\n" || line == " ") {
                        break;
                    }

                    if (line.rfind('-', 0)) {
                        // Split the string into a key-value pair
                        auto        pos = line.find(':', 0);
                        std::string key = line.substr(0, pos);
                        std::string val = line.substr(pos + 1);

                        // Parse a specific object
                        object = this->parse_line(key, val);
                    } else {
                        continue;
                    }

                    result.push_back(object);
                }

                return result;
            }
        };

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
    auto parse_functor(const FuncArgs& args) -> std::vector<T>;

    template <>
    auto parse_functor<Level::Entity>(const FuncArgs& args) -> std::vector<Level::Entity>;

    template <>
    auto parse_functor<Level::Vec2>(const FuncArgs& args) -> std::vector<Level::Vec2>;

    template <>
    auto parse_functor<Level::Line>(const FuncArgs& args) -> std::vector<Level::Line>;

    template <>
    auto parse_functor<Level::Side>(const FuncArgs& args) -> std::vector<Level::Side>;

    template <>
    auto parse_functor<Level::Sector>(const FuncArgs& args) -> std::vector<Level::Sector>;

} // namespace YAML::Types
