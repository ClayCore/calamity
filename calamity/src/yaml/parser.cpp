#include "parser.hpp"

namespace YAML {
    auto parse(const std::vector<std::string>& data) -> void {
        for (const auto& i : data) {
            std::cout << i << std::endl;
        }
    }
} // namespace YAML
