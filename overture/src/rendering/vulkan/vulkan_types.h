#pragma once

#include <defines.h>

#include <vulkan/vulkan.h>

namespace vk {
	struct VulkanDevice {
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		VkCommandPool commandPool;

		uint32_t graphicsFamily;
		uint32_t presentFamily;
	};

	struct VulkanContext {
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkSurfaceKHR surface;
		VulkanDevice device;
	};

	struct VertexLayout {};

	struct VertexBuffer {};

	struct IndexBuffer {};

	struct Shader {};

	struct Program {};
}
