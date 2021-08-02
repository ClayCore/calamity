#include "parser.hpp"
#include "lookup.hpp"
#include "types.hpp"

namespace YAML {
    auto parse(std::vector<std::string>& data) -> void {
        using namespace Types::Level;
        // Strip all single quotes and spaces
        for (auto& it : data) {
            it.erase(std::remove_if(it.begin(), it.end(), [](char x) { return '\'' == x; }), it.end());
            it.erase(std::remove_if(it.begin(), it.end(), [](char x) { return ' ' == x; }), it.end());
        }

        for (auto it = data.begin(); it < data.end(); ++it) {
            std::string current_line = *it;

            // Index of the current line in the vector.
            // prevents parsing backwards
            usize index = (it - data.begin()) + 1;

            if (current_line.rfind("ents", 0) == 0) {
                using Functor = std::function<std::vector<Entity>(const Types::FuncArgs& args)>;

                std::cout << "ENTITIES" << std::endl;

                // Sadly, we are forced to cast these constantly...
                // Blame me for using std::any for this
                // couldn't figure out how to use std::variant with it
                auto    raw     = LUTs::PARSER_FUNCTORS["PARSE_ENTS"];
                Functor functor = std::any_cast<Functor>(raw);

                // acquire the result
                std::vector<Entity> result = functor(Types::FuncArgs{ data, index });
            } else if (current_line.rfind("verts", 0) == 0) {
                using Functor = std::function<std::vector<Vec2>(const Types::FuncArgs& args)>;

                std::cout << "VERTICES" << std::endl;

                auto    raw     = LUTs::PARSER_FUNCTORS["PARSE_VERTS"];
                Functor functor = std::any_cast<Functor>(raw);

                std::vector<Vec2> result = functor(Types::FuncArgs{ data, index });
            } else if (current_line.rfind("lines", 0) == 0) {
                using Functor = std::function<std::vector<Line>(const Types::FuncArgs& args)>;

                std::cout << "LINES" << std::endl;

                auto    raw     = LUTs::PARSER_FUNCTORS["PARSE_LINES"];
                Functor functor = std::any_cast<Functor>(raw);

                std::vector<Line> result = functor(Types::FuncArgs{ data, index });
            } else if (current_line.rfind("sides", 0) == 0) {
                using Functor = std::function<std::vector<Side>(const Types::FuncArgs& args)>;

                std::cout << "SIDES" << std::endl;

                auto    raw     = LUTs::PARSER_FUNCTORS["PARSE_SIDES"];
                Functor functor = std::any_cast<Functor>(raw);

                std::vector<Side> result = functor(Types::FuncArgs{ data, index });
            } else if (current_line.rfind("sectors", 0) == 0) {
                using Functor = std::function<std::vector<Sector>(const Types::FuncArgs& args)>;

                std::cout << "SECTORS" << std::endl;

                auto    raw       = LUTs::PARSER_FUNCTORS["PARSE_SECTORS"];
                Functor processed = std::any_cast<Functor>(raw);

                std::vector<Sector> result = processed(Types::FuncArgs{ data, index });
            }
        }
    }
} // namespace YAML
