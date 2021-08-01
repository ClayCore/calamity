#include "parser.hpp"
#include "lookup.hpp"
#include "utils/hash.hpp"

namespace YAML {
    auto parse(const std::vector<std::string>& data) -> void {
        auto data_copy = data;

        // Strip all keys and values of their single quotes
        for (auto& it : data_copy) {
            it.erase(std::remove_if(it.begin(), it.end(), [](char x) { return '\'' == x; }),
                     it.end());
        }

        // Iterate over all possible parsing actions.
        for (auto&& [key, type] : Tables::PARSING_ACTIONS) {
            // Iterate through the entire file line by line
            for (auto it = data_copy.begin(); it < data_copy.end(); ++it) {
                // Get the identification of a given line, using a hash function
                auto key_ident = Z_HashStr(*it);

                // Check for the namespace id hash
                if (key_ident == 0xa8abfea0) {
                    continue;
                }

                // Catch any possible candidates for parsing, using the predefined
                // key -> event lookup table
                std::visit(
                    [&](auto val) {
                        if (key_ident == val.get_hash()) {
                            // Call the functor responsible for parsing
                            auto index = it - data_copy.begin();
                            auto func  = val.get_func();

                            auto parsed = func(data_copy, index);
                        }
                    },
                    type);
            }
        }
    }
} // namespace YAML
