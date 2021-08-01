#include "utils/file.hpp"
#include "yaml/parser.hpp"
#include "zcommon.hpp"

auto main() -> i32 {
    std::string path =
        "S:\\wplace\\cpp\\stream_dev\\gamedev_project\\calamity\\assets\\maps\\e1m1.yaml";
    auto file = File::load_file(path);

    return EXIT_SUCCESS;
}
