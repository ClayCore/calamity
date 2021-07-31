#pragma once

#include "common.h"

const char* F_Basename(const char file_path[static 1]);
isize       F_Exists(const char file_path[static 1]);
usize       F_LoadFile(const char file_path[static 1], char*** output_buffer);
