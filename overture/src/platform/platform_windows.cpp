#include <platform/platform.h>
#include <iostream>

#if PLATFORM_WINDOWS

void ConsolePrint(std::string message, u8 color) {
    std::cout << message << "\n";
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
