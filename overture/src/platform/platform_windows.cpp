#include <platform/platform.h>
#include <iostream>

#if PLATFORM_WINDOWS

void ConsolePrint(std::string message, u8 color) {
    std::cout << message << "\n";
}

#endif