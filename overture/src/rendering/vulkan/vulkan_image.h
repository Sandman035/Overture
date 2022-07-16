#pragma once

#include <vulkan/vulkan.h>

#include "vulkan_types.h"

namespace vk {
	void createVulkanImage(VulkanContext context, u32 width, u32 height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags, VulkanImage* image);

	void createImageView(VulkanContext context, VkFormat format, VulkanImage* image, VkImageAspectFlags aspectFlags);
}
