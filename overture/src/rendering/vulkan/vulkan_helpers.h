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

	const std::vector<const char*> validationLayers = {
		"VL_LAYER_KHRONOS_validation"
	};

	std::vector<const char*> getRequiredExtentions();
	b8 checkValidationLayerSupport();
}
