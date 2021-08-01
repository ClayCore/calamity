#include "file.hpp"

auto File::load_file(std::string file_path) -> usize {
    std::ifstream file(file_path);
    if (file.bad()) {
        std::fprintf(stderr, "File or path invalid.\n");
        return 0;
    }

    // Read into vector
    std::vector<std::string> lines;
    std::string              line;

    usize count = 0;
    while (std::getline(file, line)) {
        lines.push_back(line);

        count += 1;
    }

    // Display
    for (auto& i : lines) {
        std::printf("\"%s\"\n", i.c_str());
    }

    return count;
}
