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
            std::string str = *it;

            // Offset from the start of the vec
            // Prevents parsing of elements backwards
            usize offset = (it - data.begin()) + 1;

            auto level = Types::Level::parse_level({ data, offset });
        }
    }
} // namespace YAML
