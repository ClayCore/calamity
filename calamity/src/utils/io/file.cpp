#include "file.hpp"

namespace Calamity::File
{
    std::optional<std::vector<std::string>> load_file(std::string file_path)
    {
        std::ifstream file(file_path);
        if (file.bad()) {
            std::fprintf(stderr, "File or path invalid.\n");
            return std::nullopt;
        }

        // Read into vector
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(file, line)) { lines.push_back(line); }

        return lines;
    }
}  // namespace Calamity::File
