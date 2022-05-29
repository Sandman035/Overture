#pragma once

#include <defines.h>
#include <string>
#include <vector>

void ConsolePrint(std::string message, u8 color);

std::vector<char> readFile(const std::string& filename);
