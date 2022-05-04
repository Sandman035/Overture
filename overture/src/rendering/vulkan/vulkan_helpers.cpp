#include "vulkan_helpers.h"

#include <GLFW/glfw3.h>

namespace vk {
	std::vector<const char*> getRequiredExtentions() {
		uint32_t glfwExtentionCount = 0;
		const char** glfwExtentions;
		glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);

		std::vector<const char*> extentions(glfwExtentions, glfwExtentions + glfwExtentionCount);

		//TODO: validation layers
		
		return extentions;
	}
}
