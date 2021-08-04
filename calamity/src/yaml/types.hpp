#pragma once

#include "utils/hash.hpp"
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
        class MapObject {
          public:
            // Parse a single line from the config file.
            virtual auto parse_line(const std::string& key, const std::string& val) -> std::shared_ptr<MapObject> {
                auto result = std::make_shared<MapObject>();

                return result;
            }

            // Parse an entire object, this is what actually gets called.
            auto parse_object(const ParseFuncArgs& args) -> std::vector<std::shared_ptr<MapObject>> {
                auto result = std::vector<std::shared_ptr<MapObject>>();
                auto object = std::make_shared<MapObject>();

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

        class Vec2 : public MapObject {
          public:
            f32 m_xpos;
            f32 m_ypos;

            virtual auto parse_line(const std::string& key, const std::string& val) -> std::shared_ptr<MapObject> {
                auto object = std::make_shared<Vec2>();
                switch (get_hash(key)) {
                    case "x"_hash: {
                        object->m_xpos = std::stod(val);
                        break;
                    }
                    case "y"_hash: {
                        object->m_ypos = std::stod(val);
                        break;
                    }
                }

                return object;
            }
        };

        class Entity : public MapObject {
          public:
            f32 m_xpos;
            f32 m_ypos;
            u16 m_angle;
            u16 m_type;

            virtual auto parse_line(const std::string& key, const std::string& val) -> std::shared_ptr<MapObject> {
                auto object = std::make_shared<Entity>();
                switch (get_hash(key)) {
                    case "x"_hash: {
                        object->m_xpos = std::stod(val);
                    } break;
                    case "y"_hash: {
                        object->m_ypos = std::stod(val);
                    } break;
                    case "angle"_hash: {
                        object->m_angle = static_cast<u16>(std::stod(val));
                    } break;
                    case "type"_hash: {
                        object->m_type = static_cast<u16>(std::stod(val));
                    } break;
                }

                return object;
            }
        };

        class Line : public MapObject {
          public:
            u16 m_start;
            u16 m_end;

            virtual auto parse_line(const std::string& key, const std::string& val) -> std::shared_ptr<MapObject> {
                auto object = std::make_shared<Line>();
                switch (get_hash(key)) {
                    case "v1"_hash: {
                        object->m_start = static_cast<u16>(std::stoul(val));
                    } break;
                    case "v2"_hash: {
                        object->m_end = static_cast<u16>(std::stoul(val));
                    } break;
                }

                return object;
            }
        };

        class Side : public MapObject {
          public:
            u16 m_sector_index;

            virtual auto parse_line(const std::string& key, const std::string& val) -> std::shared_ptr<MapObject> {
                auto object = std::make_shared<Side>();
                switch (get_hash(key)) {
                    case "sector"_hash: {
                        object->m_sector_index = static_cast<u16>(std::stoul(val));
                    } break;
                }

                return object;
            }
        };

        class Sector : public MapObject {
          public:
            i16 m_floor_height;
            i16 m_ceiling_height;

            std::string m_floor_texture;
            std::string m_ceiling_texture;

            u8 m_light_level;

            virtual auto parse_line(const std::string& key, const std::string& val) -> std::shared_ptr<MapObject> {
                auto object = std::make_shared<Sector>();
                switch (get_hash(key)) {
                    case "floor_height"_hash: {
                        object->m_floor_height = static_cast<u16>(std::stoul(val));
                    } break;
                    case "ceil_height"_hash: {
                        object->m_ceiling_height = static_cast<u16>(std::stoul(val));
                    } break;
                    case "floor_tex"_hash: {
                        object->m_floor_texture = val;
                    } break;
                    case "ceil_tex"_hash: {
                        object->m_floor_texture = val;
                    } break;
                    case "light_level"_hash: {
                        object->m_light_level = static_cast<u8>(std::stol(val));
                    } break;
                }

                return object;
            }
        };

        struct LevelData {
            std::vector<Entity> entities;
            std::vector<Vec2>   verts;
            std::vector<Line>   lines;
            std::vector<Side>   sides;
            std::vector<Sector> sectors;
        };

        // ============================
        // = Map tags lookup table ====
        // ============================

        // Used for parsing different types of level objects from map files
        constexpr const usize NUM_MAP_TAGS = 5;

        const std::array<std::shared_ptr<MapObject>, NUM_MAP_TAGS> MAP_OBJECTS = {
            std::make_shared<Entity>(), std::make_shared<Vec2>(),   std::make_shared<Line>(),
            std::make_shared<Side>(),   std::make_shared<Sector>(),
        };

        // Goes through all map objects
        // and parses them one by one.
        // Then puts back the parsed and well-defined
        // map objects, into the LevelData structure.
        template <class T>
        auto get_level_object(const ParseFuncArgs& args, usize index) -> std::vector<T> {
            auto& map_objs = MAP_OBJECTS;

            std::vector<T> objects = {};
            auto           ptrs    = map_objs[index]->parse_object({ args.data, args.offset });
            for (usize i = 0; i < ptrs.size(); ++i) {
                auto object = std::dynamic_pointer_cast<T>(ptrs[i]);

                objects.push_back(*object);
            }

            return objects;
        }

        auto parse_level(const ParseFuncArgs& args) -> LevelData {
            LevelData level = {};

            level.entities = get_level_object<Entity>(args, 0);
            level.verts    = get_level_object<Vec2>(args, 1);
            level.lines    = get_level_object<Line>(args, 2);
            level.sides    = get_level_object<Side>(args, 3);
            level.sectors  = get_level_object<Sector>(args, 4);

            std::cout << "Vertices\n";
            for (auto& v : level.verts) {
                std::printf("\t[%f]:[%f]\n", v.m_xpos, v.m_ypos);
            }

            std::cout << "\nEntities\n";
            for (auto& v : level.entities) {
                std::printf("\t(%d @ %d) [%f]:[%f]\n", v.m_type, v.m_angle, v.m_xpos, v.m_ypos);
            }

            std::cout << "\nLines\n";
            for (auto& v : level.lines) {
                std::printf("\t[%d]:[%d]\n", v.m_start, v.m_end);
            }

            std::cout << "\nSides\n";
            for (auto& v : level.sides) {
                std::printf("\t[%d]\n", v.m_sector_index);
            }

            return level;
        }
    } // namespace Level
} // namespace YAML::Types
