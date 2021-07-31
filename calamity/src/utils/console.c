#include "console.h"

// Clears the screen
void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#else
    system("cls");
#endif
}
