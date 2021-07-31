#include "file.h"
#include "log.h"

// Returns the filename without the path
const string_t F_Basename(const char file_path[static 1]) {
    const char* basename =
        (basename = strrchr(file_path, '\\')) ? ++basename : (basename = file_path);

    return basename;
}

// Checks if any file exists.
isize F_Exists(const char file_path[static 1]) {
    FILE* fd;
    if ((fd = fopen(file_path, "r")) != NULL) {
        log_trace("F_Exists(): File \"%s\" exists", file_path);
        fclose(fd);

        return 1;
    } else {
        log_error("F_Exists(): Failed to open file.");

        return 0;
    }
}

// Loads a file line-by-line into the output_buffer
usize F_LoadFile(const char file_path[static 1], string_t* output_buffer) {
    log_trace("F_LoadFile(): Opening \"%s\"", file_path);

    usize MAX_LEN   = 512;
    usize MAX_LINES = 4096;

    FILE* fd;
    usize count = 0;
    usize read  = 0;

    // Check if the file is readable
    fd = fopen(file_path, "r");
    if (!fd) {
        log_error("F_LoadFile(): Failed to open file.");
        return read;
    }

    if (*output_buffer == NULL) {
        *output_buffer = calloc(1, MAX_LINES);
    }

    char  line[MAX_LEN];
    usize len = 0;
    while (fgets(line, sizeof(line), fd)) {
        // Strip newlines
        line[strcspn(line, "\n")] = 0;

        len = strlen(line);
        read += len;

        (*output_buffer)[count] = calloc(1, len);
        strncpy((*output_buffer)[count], line, len);

        count += 1;
    }

    log_trace("F_LoadFile(): Read %" PRIu32 " lines and %" PRIu32 " bytes", count, read);

    fclose(fd);

    return read;
}
