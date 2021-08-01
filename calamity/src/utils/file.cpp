#include "file.hpp"

namespace File {
    auto load_file(std::string file_path) -> std::vector<std::string> {
        std::ifstream file(file_path);
        if (file.bad()) {
            std::fprintf(stderr, "File or path invalid.\n");
            return;
        }

        // Read into vector
        std::vector<std::string> lines;
        std::string              line;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        return lines;
    }
} // namespace File
