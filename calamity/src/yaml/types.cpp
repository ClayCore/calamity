#include "types.hpp"

namespace YAML::Types {
    template <class T>
    auto parse_functor(const FuncArgs& args) -> void {
        std::cerr << "Called unspecialized functor." << std::endl;
        return;
    }

    template <>
    auto parse_functor<Level::Entity>(const FuncArgs& args) -> void {
        for (auto it = args.data.begin() + args.index; it < args.data.end(); ++it) {
            // Get the current index (which line) from the iterator
            usize       cur_idx = it - args.data.begin();
            std::string line    = *it;

            // Break when we hit newlines or empty strings
            // these signify the end of our parsing block
            if (line == "\n" || line == "") {
                break;
            }

            // If no "end of stream" markers have been found
            // parse the following lines as dictionaries in arrays.
            if (line.rfind('-', 0)) {
                std::string value = line;

                // Identify where in the string the value starts and key ends
                auto pos = value.find(':', 0);

                // Erase it
                value.erase(0, pos + 1);

                std::cout << "\tParsed: [" << value << "]" << std::endl;
            } else {
                continue;
            }
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
