#ifndef UTILS_H
#define UTILS_H

// Use preprocessor directives for cross-platform compatibility.
#ifdef _WIN32
#include <windows.h> // For the Sleep function on Windows.
#else
#include <unistd.h> // For the usleep function on Linux/macOS.
#endif

// Pauses execution for a specified number of milliseconds.
static inline void sleep_ms(int milliseconds) {
#ifdef _WIN32
    // Windows' Sleep function takes milliseconds.
    Sleep(milliseconds);
#else
    // Linux's usleep function takes microseconds.
    usleep(milliseconds * 1000);
#endif
}

#endif // UTILS_H