#pragma once

#include <defines.h>

#include <vulkan/vulkan.h>
#include <vector>

namespace vk {
	struct VulkanImage {
		VkImage handle;
		VkImageView view;

		VkDeviceMemory memory;

		u32 width;
		u32 height;
	};

	struct VulkanSwapchain {
		VkSurfaceFormatKHR imageFormat;
		u8 maxFrames;

		VkSwapchainKHR handle;

		u32 imageCount;
		std::vector<VkImage> swapchainImages;
		std::vector<VkImageView> swapchainImageViews;

		std::vector<VkFramebuffer> framebuffers;
	};

	struct VulkanSwapchainSupportInfo {
		VkSurfaceCapabilitiesKHR capabilities;

		u32 formatCount;
		std::vector<VkSurfaceFormatKHR> formats;

		u32 presentModeCount;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct VulkanDevice {
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		VkCommandPool commandPool;

		VulkanSwapchainSupportInfo swapchainSupport;

		uint32_t graphicsFamily;
		uint32_t presentFamily;

		VkFormat depthFormat;
	};

	struct VulkanContext {
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkSurfaceKHR surface;
		VulkanDevice device;
		VulkanSwapchain swapchain;
	};

	struct VertexLayout {};

	struct VertexBuffer {};

	struct IndexBuffer {};

	struct Shader {};

	struct Program {};
}
