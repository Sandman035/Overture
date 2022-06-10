#pragma once

#include <defines.h>

#include "vulkan_types.h"

namespace vk {
	void createSwapchain(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain);
	void recreateSwapchain(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain);
	void destroySwapchain(VulkanContext* context, VulkanSwapchain* swapchain);
}
