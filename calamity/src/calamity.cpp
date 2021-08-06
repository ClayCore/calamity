#include "graphics/manager.hpp"
#include "yaml/manager.hpp"
#include "zcommon.hpp"

i32
main()
{
    // YAML PARSING TEST
    // std::string path = "S:\\wplace\\cpp\\stream_dev\\gamedev_project\\calamity\\assets\\maps\\e1m1.yaml";
    // Yaml::M_Init(path);

    // RENDERER TEST
    GFX::R_Init();

    return EXIT_SUCCESS;
}
