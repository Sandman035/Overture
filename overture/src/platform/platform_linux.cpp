#include <platform/platform.h>
#include <iostream>

#if PLATFORM_LINUX

void ConsolePrint(std::string message, u8 color) {
    const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    // printf("\033[%sm%s\033[0m", colour_strings[colour], message);
    std::cout << "\033[" << colour_strings[color] << "m" << message << "\033[0m\n";
}

#endif