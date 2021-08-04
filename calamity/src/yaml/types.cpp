#include "types.hpp"
#include "lookup.hpp"

namespace YAML::Types::Level {
    template <class T>
    auto object_ref(const ParseFuncArgs& args, usize index) -> std::vector<T> {
        auto& map_objs = LUTs::MAP_OBJECTS;

        auto get_obj = [&]() -> std::vector<T> {
            std::vector<T> objects = {};

            auto ptrs = map_objs[index]->parse_object({ args.data, args.offset });
            for (auto& i : ptrs) {
                T object = *i;
                objects.push_back(object);
            }

            return objects;
        };

        std::vector<T> result = get_obj();
        return result;
    }

    auto parse_level(const ParseFuncArgs& args) -> LevelData {
        LevelData level = {};

        level.entities = object_ref<Entity>(args, 0);
        level.verts    = object_ref<Vec2>(args, 1);
        level.lines    = object_ref<Line>(args, 2);
        level.sides    = object_ref<Side>(args, 3);
        level.sectors  = object_ref<Sector>(args, 4);

        return level;
    }
} // namespace YAML::Types::Level
