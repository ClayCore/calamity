#include "parser.hpp"
#include "lookup.hpp"
#include "types.hpp"

namespace YAML {
    auto parse(std::vector<std::string>& data) -> void {
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
                std::cout << "ENTITIES" << std::endl;
                LUTs::PARSER_FUNCTORS["PARSE_ENTS"](Types::FuncArgs{ data, index });
            } else if (current_line.rfind("verts", 0) == 0) {
                std::cout << "VERTICES" << std::endl;
                LUTs::PARSER_FUNCTORS["PARSE_VERTS"](Types::FuncArgs{ data, index });
            } else if (current_line.rfind("lines", 0) == 0) {
                std::cout << "LINES" << std::endl;
                LUTs::PARSER_FUNCTORS["PARSE_LINES"](Types::FuncArgs{ data, index });
            } else if (current_line.rfind("sides", 0) == 0) {
                std::cout << "SIDES" << std::endl;
                LUTs::PARSER_FUNCTORS["PARSE_SIDES"](Types::FuncArgs{ data, index });
            } else if (current_line.rfind("sectors", 0) == 0) {
                std::cout << "SECTORS" << std::endl;
                LUTs::PARSER_FUNCTORS["PARSE_SECTORS"](Types::FuncArgs{ data, index });
            }
        }
    }
} // namespace YAML
