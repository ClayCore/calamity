#include "yaml/manager.hpp"
#include "zcommon.hpp"

auto main() -> i32 {
    std::string path = "S:\\wplace\\cpp\\stream_dev\\gamedev_project\\calamity\\assets\\maps\\e1m1.yaml";

    Yaml::M_Init(path);

    // RENDERER TEST
    // Renderer::R_Init();

    return EXIT_SUCCESS;
}
