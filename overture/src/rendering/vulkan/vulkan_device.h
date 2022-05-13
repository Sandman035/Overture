#pragma once

#include <defines.h>

#include "vulkan_types.h"

namespace vk {
	void createDevice(VulkanContext* context);
	void destroyDevice(VulkanContext* context);
	void selecPhysicalDevice(VulkanContext* context);
	b8 isDeviceSuitable(VkPhysicalDevice device, VulkanContext* context);
};
