#pragma once

#include <defines.h>
#include <vector>

#include <string>
#include <vulkan/vulkan.h>

#include "vulkan_types.h"

namespace vk {
	struct initInfo {
		i32 width;
		i32 height;
		std::string name;
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	std::vector<const char*> getRequiredExtentions();
	b8 checkValidationLayerSupport();

	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
}
