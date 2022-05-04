#pragma once

#include <defines.h>
#include <vector>

#include <string>

namespace vk {
	struct initInfo {
		i32 width;
		i32 height;
		std::string name;
	};

	std::vector<const char*> getRequiredExtentions();
}
