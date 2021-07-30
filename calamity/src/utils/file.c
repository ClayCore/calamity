#include "file.h"
#include "log.h"

// Returns the filename without the path
const char* F_Basename(const char* file_path) {
    char* basename;
    (basename = strrchr(file_path, '\\')) ? ++basename : (basename = file_path);

    return basename;
}

// Checks if any file exists.
isize F_Exists(const char* file_path) {
    FILE* fd;
    if ((fd = fopen(file_path, "r")) != NULL) {
        fclose(fd);

        return 0;
    } else {
        log_error("Failed to open file.");

        return -1;
    }
}

// Loads the file and logs it.
// TODO: Return the read file contents into a buffer
isize F_LoadFile(const char* file_path) {
    if (*file_path == '\0') {
        log_error("F_LoadFile(): \"%s\" is empty or invalid!", file_path);

        return -1;
    } else {
        log_trace("F_LoadFile(): Opening \"%s\"", file_path);
        i32 MAX_LEN = 512;

        FILE* fd;
        usize count = 0;
        isize read  = 0;

        fd = fopen(file_path, "r");
        if (!fd) {
            log_error("Failed to open file.");
            return read;
        }

        char  line[MAX_LEN];
        usize len = 0;
        while (fgets(line, sizeof(line), fd)) {
            // Strip newlines
            line[strcspn(line, "\n")] = 0;

            len = strlen(line);
            read += len;

            log_trace("F_LoadFile(): [%d: \"%s\"]: %s", count, F_Basename(file_path), line);
            count += 1;
        }

        fclose(fd);

        return read;
    }
}
