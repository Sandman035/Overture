#pragma once

#include <cstdint>
#include <defines.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include <vector>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	b8 isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class VulkanRenderer {
	public:
		void init();
		void shutdown();
		
	private:
		void onResize();

		b8 createInstance();
		void setupDebugCallback();
		void createSurface();
		VkPhysicalDevice pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createSwapChainImageViews();
		void createRenderPasses();
		
		b8 checkValidationLayerSupport();
		b8 validationLayerSupported;
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		b8 isDeviceSuitable(VkPhysicalDevice device);

		std::vector<const char*> getRequiredExtensions();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice logicalDevice;
		VkQueue graphicsQueue;
		VkSurfaceKHR surface;
		VkQueue presentQueue;

		const std::vector<const char*> validationLayers = {
    		"VK_LAYER_KHRONOS_validation"
		};
};
