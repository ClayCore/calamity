#include "types.hpp"

namespace YAML::Types {
    template <class T>
    auto parse_functor(const FuncArgs& args) -> void {
        std::cerr << "Called unspecialized functor." << std::endl;
        return;
    }

    template <>
    auto parse_functor<Level::Entity>(const FuncArgs& args) -> void {
        Level::Entity ent     = {};
        Level::Vec2   ent_pos = {};

        std::vector<Level::Entity> entities;
        for (auto it = args.data.begin() + args.index; it < args.data.end(); ++it) {
            std::string line = *it;

            // Break when we hit newlines or empty strings
            // these signify the end of our parsing block
            if (line == "\n" || line == "") {
                break;
            }

            // If no "end of stream" markers have been found
            // parse the following lines as dictionaries in arrays.
            if (line.rfind('-', 0)) {
                // Identify where in the string the value starts and key ends
                auto pos = line.find(':', 0);

                // Split the string into a key-value pair
                std::string key   = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                // No switch statements for non-integral types...
                if (key == "x") {
                    ent_pos.x = std::stod(value);
                } else if (key == "y") {
                    ent_pos.y = std::stod(value);
                } else if (key == "angle") {
                    ent.angle = static_cast<u16>(std::stod(value));
                } else if (key == "type") {
                    ent.type = static_cast<u16>(std::stod(value));
                }

                std::cout << "\tParsed: [" << key << "]:[" << value << "]" << std::endl;
            } else {
                continue;
            }

            // Save the entity into a vector
            ent.pos = ent_pos;
            entities.push_back(ent);
        }
        return;
    }

    template <>
    auto parse_functor<Level::Vec2>(const FuncArgs& args) -> void {}

    template <>
    auto parse_functor<Level::Line>(const FuncArgs& args) -> void {}

    template <>
    auto parse_functor<Level::Side>(const FuncArgs& args) -> void {}

    template <>
    auto parse_functor<Level::Sector>(const FuncArgs& args) -> void {}
} // namespace YAML::Types
