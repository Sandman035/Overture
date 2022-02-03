#include <platform/platform.h>

#include <core/log.h>

#include <iostream>
#include <fstream>

#if PLATFORM_LINUX

void ConsolePrint(std::string message, u8 color) {
    const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    // printf("\033[%sm%s\033[0m", colour_strings[colour], message);
    std::cout << "\033[" << colour_strings[color] << "m" << message << "\033[0m\n";
}

std::vector<char> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if(!file.is_open()) {
		ERROR("failed to open file: %s", filename.c_str());
		return {};
	}

	size_t fileSize = (size_t) file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

#endif
