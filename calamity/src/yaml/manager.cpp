#include "manager.hpp"
#include "utils/file.hpp"

namespace Yaml
{
    struct DataOffset {
        const std::vector<std::string>& data;

        usize offset;
    };

    /* NOTE:                                                       = **
    ** Do we really need to do like 50 round trips around the file = **
    ** just to parse like 5 or 6 sections?                         = **
    **                                                             = **
    ** There needs to be a better way. I need to think of one.     = **
    ** For now this code does not work, so don't bother            = **
    ** Ignore and move on                                          = **/
    static void
    M_ParseYaml(const DataOffset& args)
    {
        for (auto it = args.data.begin() + args.offset; it < args.data.end(); ++it) {
            std::string line = *it;

            // Newlines and empty strings indicate the end
            // of a block
            if (line == "\n" || line == " ") {
                break;
            }

            std::printf("Got line: [%s] at offset: [%u]\n", line.c_str(), args.offset);

            if (line.rfind('-', 0) != line.npos) {
                auto pos = line.find(':', 0);
                auto key = line.substr(0, pos);
                auto val = line.substr(pos + 1);

                // Parse object
                // std::printf("\tParsed: [%s]: [%s]\n", key.c_str(), val.c_str());
            } else {
                continue;
            }
        }
    }

    // Parse and deserialize all map files, stored in
    // /calamity/src/assets/maps/*
    static void
    M_ParseLevel(std::vector<std::string>& raw_data)
    {
        for (auto& it : raw_data) {
            // Removes any single quotes and spaces
            auto strip = [](char x) { return x == '\'' || x == ' '; };

            it.erase(std::remove_if(it.begin(), it.end(), strip), it.end());
        }

        for (auto off = 0; off < 5; ++off) {
            for (auto it = raw_data.begin(); it < raw_data.end(); ++it) {
                std::string str = *it;

                usize offset = static_cast<usize>((it - raw_data.begin()) + 1);

                // Do something with the objects and offsets
            }
        }
    }

    // TODO: change to `std::vector<std::string>`
    void
    M_Init(const std::string& path)
    {
        std::cout << "Initialized YAML parsing manager" << std::endl;

        // Parse all the maps and levels
        // for now there's only one.
        if (auto data = File::load_file(path)) {
            M_ParseLevel(*data);
        }
    }
} // namespace Yaml
