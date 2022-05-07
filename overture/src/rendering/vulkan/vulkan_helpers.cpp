#include "vulkan_helpers.h"

#include <core/log.h>

#include <GLFW/glfw3.h>

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

	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		const char* type;
		
		switch (messageType) {
			case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
				type = "GENERAL: ";
				break;
			case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
				type = "VALIDATION: ";
				break;
			case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
				type = "PERFORMANCE: ";
				break;
			default:
				type = "";
				break;
		}

		switch (messageSeverity) {
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				TRACE("Vulkan: validation layer: %s%s", type, pCallbackData->pMessage);
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				INFO("Vulkan: validation layer: %s%s", type, pCallbackData->pMessage);
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				WARN("Vulkan: validation layer: %s%s", type, pCallbackData->pMessage);
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				ERROR("Vulkan: validation layer: %s%s", type, pCallbackData->pMessage);
				break;
			default:
				DEBUG("Vulkan: validation layer: %s%s", type, pCallbackData->pMessage);
				break;
		}

		return VK_FALSE;
	}
}
