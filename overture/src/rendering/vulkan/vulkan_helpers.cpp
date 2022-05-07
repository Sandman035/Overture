#include "vulkan_helpers.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string.h>

namespace vk {
	std::vector<const char*> getRequiredExtentions() {
		uint32_t glfwExtentionCount = 0;
		const char** glfwExtentions;
		glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);

		std::vector<const char*> extentions(glfwExtentions, glfwExtentions + glfwExtentionCount);

#if RELEASE == 1
		if (checkValidationLayerSupport()) {
			extentions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
#endif

		return extentions;
	}

	b8 checkValidationLayerSupport() {
		uint32_t layercount;
		vkEnumerateInstanceLayerProperties(&layercount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layercount);
		vkEnumerateInstanceLayerProperties(&layercount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& LayerProperties : availableLayers) {
				if (strcmp(layerName, LayerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			
			if (!layerFound) {
				return false;
			}
		}
		return true;
	}
}
