#include "parser.hpp"
#include "utils/hash.hpp"

namespace YAML {
    const std::unordered_map<std::string, u32> LEVEL_TAGS = {
        { "ENTITIES", 0xb17ff827 }, { "VERTICES", 0xe8fc34a1 }, { "LINES", 0xf039db38 },
        { "SIDES", 0xa5c9025 },     { "SECTORS", 0x389eb4b0 },
    };

    auto parse_ents(const std::vector<std::string>& data, usize index) -> void {
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                return;
            }

            std::cout << "Ent: \"" << data[i] << "\"" << std::endl;
        }
    }

    auto parse_verts(const std::vector<std::string>& data, usize index) -> void {
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                return;
            }

            std::cout << "Vert: \"" << data[i] << "\"" << std::endl;
        }
    }

    auto parse_lines(const std::vector<std::string>& data, usize index) -> void {
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                return;
            }

            std::cout << "Line: \"" << data[i] << "\"" << std::endl;
        }
    }

    auto parse_sides(const std::vector<std::string>& data, usize index) -> void {
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                return;
            }

            std::cout << "Side: \"" << data[i] << "\"" << std::endl;
        }
    }

    auto parse_sectors(const std::vector<std::string>& data, usize index) -> void {
        for (usize i = index; i < data.size(); ++i) {
            // We reached the end of the stream for this data block
            if (data[i] == "\n" || data[i] == "") {
                return;
            }

            std::cout << "Sector: \"" << data[i] << "\"" << std::endl;
        }
    }

    auto parse(const std::vector<std::string>& data) -> void {
        // Parse line by line
        usize index = 0;
        for (auto& i : data) {
            // Check for the namespace id
            if (Z_HashStr(i) == 0x254c893c) {
                index += 1;
                continue;
            }

            // Parse the known level tags
            auto hash = Z_HashStr(i);
            if (hash == LEVEL_TAGS.at("ENTITIES")) {
                parse_ents(std::move(data), index);
                continue;
            } else if (hash == LEVEL_TAGS.at("VERTICES")) {
                parse_verts(std::move(data), index);
                continue;
            } else if (hash == LEVEL_TAGS.at("LINES")) {
                parse_lines(std::move(data), index);
                continue;
            } else if (hash == LEVEL_TAGS.at("SIDES")) {
                parse_sides(std::move(data), index);
                continue;
            } else if (hash == LEVEL_TAGS.at("SECTORS")) {
                parse_sectors(std::move(data), index);
                continue;
            } else {
                index += 1;
            }
        }
    }
} // namespace YAML
