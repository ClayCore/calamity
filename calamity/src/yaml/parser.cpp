#include "parser.hpp"
#include "lookup.hpp"

namespace YAML {
    auto parse(const std::vector<std::string>& data) -> void {
        auto data_copy = data;

        // Strip all keys and values of their single quotes
        for (auto& it : data_copy) {
            it.erase(std::remove_if(it.begin(), it.end(), [](char x) { return '\'' == x; }),
                     it.end());

            // std::printf("\"%-25s\": [0x%" PRIxPTR "]\n", it.c_str(),
            // std::hash<std::string>()(it));
        }

        // Iterate over all possible parsing actions.
        for (auto&& [key, type] : LookupTables::LEVEL_PARSER) {
            // Iterate through the entire file line by line
            for (auto it = data_copy.begin(); it < data_copy.end(); ++it) {
                // Get the identification of a given line, using a hash function
                auto key_ident = std::hash<std::string>()(*it);

                // Check for the namespace id hash
                if (key_ident == std::hash<std::string>()("namespace: calamity")) {
                    continue;
                }

                // Catch any possible candidates for parsing, using the predefined
                // key -> event lookup table
                std::visit(
                    [&](auto val) {
                        if (key_ident == val.get_hash()) {
                            // Call the functor responsible for parsing
                            usize index = (it - data_copy.begin()) + 1;

                            std::printf("\"%-10s\": \n", key.c_str());
                            auto parsed_data = val.get_parser({ data_copy, index });
                        }
                    },
                    type);
            }
        }
    }
} // namespace YAML
