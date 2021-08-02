#include "types.hpp"

namespace YAML::Types {
    namespace Funcs {
        auto gen_hash(usize key) noexcept -> u64 {
            switch (key) {
                // ENTITIES
                case 0: {
                    return std::hash<std::string>()("ents:");
                } break;
                // VERTICES
                case 1: {
                    return std::hash<std::string>()("verts:");
                } break;
                // LINES
                case 2: {
                    return std::hash<std::string>()("lines:");
                } break;
                // SIDES
                case 3: {
                    return std::hash<std::string>()("sides:");
                } break;
                // SECTORS
                case 4: {
                    return std::hash<std::string>()("sectors:");
                } break;
                default: {
                    return 0;
                }
            }
        }
    } // namespace Funcs
} // namespace YAML::Types
