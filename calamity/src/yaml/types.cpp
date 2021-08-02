#include "types.hpp"

namespace YAML::Types {
    template <class T>
    auto parse_functor(const FuncArgs& args) -> std::vector<T> {
        std::vector<T> result;
        std::cerr << "Called unspecialized functor." << std::endl;
        return result;
    }

    template <>
    auto parse_functor<Level::Entity>(const FuncArgs& args) -> std::vector<Level::Entity> {
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
        return entities;
    }

    template <>
    auto parse_functor<Level::Vec2>(const FuncArgs& args) -> std::vector<Level::Vec2> {
        Level::Vec2 vert = {};

        std::vector<Level::Vec2> verts;
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
                    vert.x = std::stod(value);
                } else if (key == "y") {
                    vert.y = std::stod(value);
                }

                std::cout << "\tParsed: [" << key << "]:[" << value << "]" << std::endl;
            } else {
                continue;
            }

            // Save the entity into a vector
            verts.push_back(vert);
        }
        return verts;
    }

    template <>
    auto parse_functor<Level::Line>(const FuncArgs& args) -> std::vector<Level::Line> {
        Level::Line line_obj = {};

        std::vector<Level::Line> lines;
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
                if (key == "v1") {
                    line_obj.start = static_cast<u16>(std::stoul(value));
                } else if (key == "v2") {
                    line_obj.end = static_cast<u16>(std::stoul(value));
                }

                std::cout << "\tParsed: [" << key << "]:[" << value << "]" << std::endl;
            } else {
                continue;
            }

            // Save the entity into a vector
            lines.push_back(line_obj);
        }
        return lines;
    }

    template <>
    auto parse_functor<Level::Side>(const FuncArgs& args) -> std::vector<Level::Side> {
        Level::Side side = {};

        std::vector<Level::Side> sides;
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
                if (key == "sector") {
                    side.sector_index = static_cast<u16>(std::stoul(value));
                }

                std::cout << "\tParsed: [" << key << "]:[" << value << "]" << std::endl;
            } else {
                continue;
            }

            // Save the entity into a vector
            sides.push_back(side);
        }
        return sides;
    }

    template <>
    auto parse_functor<Level::Sector>(const FuncArgs& args) -> std::vector<Level::Sector> {
        Level::Sector sector = {};

        std::vector<Level::Sector> sectors;
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
                if (key == "floor_height") {
                    sector.floor_height = static_cast<i16>(std::stol(value));
                } else if (key == "ceil_height") {
                    sector.ceiling_height = static_cast<i16>(std::stol(value));
                } else if (key == "floor_tex") {
                    sector.floor_texture = value;
                } else if (key == "ceil_tex") {
                    sector.ceiling_texture = value;
                } else if (key == "ceil_tex") {
                    sector.light_level = static_cast<u8>(std::stol(value));
                }

                std::cout << "\tParsed: [" << key << "]:[" << value << "]" << std::endl;
            } else {
                continue;
            }

            // Save the entity into a vector
            sectors.push_back(sector);
        }
        return sectors;
    }
} // namespace YAML::Types
