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

    char   file_path[]   = "S:\\wplace\\cpp\\stream_dev\\gamedev_project\\calamity\\build.yaml";
    char** output_buffer = NULL;

    if (F_Exists(file_path)) {
        F_LoadFile(file_path, &output_buffer);
    }

    usize count = 0;
    while (output_buffer[count] != NULL) {
        count++;
    }

    for (usize i = 0; i < count; ++i) {
        log_trace("%s", output_buffer[i]);
        free(output_buffer[i]);
    }

    free(output_buffer);
    return EXIT_SUCCESS;
}
