#include "utils/file.hpp"
#include "yaml/parser.hpp"
#include "zcommon.hpp"

auto main() -> i32 {
    std::string path =
        "S:\\wplace\\cpp\\stream_dev\\gamedev_project\\calamity\\assets\\maps\\e1m1.yaml";

    if (auto data = File::load_file(path)) {
        YAML::parse(*data);
    }

    return EXIT_SUCCESS;
}
