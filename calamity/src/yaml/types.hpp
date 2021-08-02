#pragma once

#include "zcommon.hpp"

namespace YAML::Types {
    // Utility functions
    namespace Funcs {
        auto gen_hash(usize key) noexcept -> u64;
    } // namespace Funcs

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

        struct Level {
            std::vector<Entity> entities;
            std::vector<Vec2>   vertices;
            std::vector<Line>   lines;
            std::vector<Side>   sides;
            std::vector<Sector> sectors;
        };

        enum Object : usize {
            entity = 0,
            vert,
            line,
            side,
            sector,
        };

        // This structure lets us parse any level data
        template <typename T> struct Parser {
          public:
            // Utility structure for holding arguments to functors
            struct Args {
                const std::vector<std::string>& data;

                usize index;
            };

          private:
            // Typedefs for less typing.
            // =========================

            // The return value of a functor
            using RetVal = std::vector<T>;

            // The functor type itself
            using Functor = std::function<RetVal(const Args& args)>;

            u64   m_hash;
            usize m_type;
            // Functor m_functor;

          public:
            Parser(u64 hash, usize type) {
                this->m_hash = hash;
                this->m_type = type;
            }

            // Parser methods
            auto get_hash() -> u64 {
                return this->m_hash;
            }

            auto get_parser(const Args& args) -> RetVal {
                return Parser<T>::parse(args, this->m_type);
            }

            // List of functors available for the parser.
            static auto parse(const Args& args, usize type) -> RetVal {
                RetVal parsed_data;

                Object type_obj = Object(type);
                for (auto idx = args.index; idx < args.data.size(); ++idx) {
                    std::string line = args.data[idx];

                    // Block mapping has reached the end
                    if (line == "\n" || line == "") {
                        break;
                    }

                    switch (type_obj) {
                        case Object::entity: {
                            std::cout << "\t" << line << std::endl;
                        } break;
                        case Object::vert: {
                            std::cout << "\t" << line << std::endl;
                        } break;
                        case Object::line: {
                            std::cout << "\t" << line << std::endl;
                        } break;
                        case Object::side: {
                            std::cout << "\t" << line << std::endl;
                        } break;
                        case Object::sector: {
                            std::cout << "\t" << line << std::endl;
                        } break;
                        default: {
                            std::cerr << "Invalid or unsupported parse index" << std::endl;
                        } break;
                    }
                }

                return parsed_data;
            }
        };

    } // namespace Level
} // namespace YAML::Types
