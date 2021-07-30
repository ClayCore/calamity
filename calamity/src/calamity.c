#include "common.h"
#include "utils/file.h"
#include "utils/log.h"

void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#else
    system("cls");
#endif
}

i32 main() {
    clear();

    log_info("Init(): Initializing game engine...");

    char file_path[] = "S:\\wplace\\cpp\\stream_dev\\gamedev_project\\calamity\\res\\temp.txt";

    if (F_Exists(file_path) == 0) {
        F_LoadFile(file_path);
    }

    return EXIT_SUCCESS;
}
