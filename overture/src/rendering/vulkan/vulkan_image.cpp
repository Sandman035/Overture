#include "vulkan_image.h"

namespace vk {
	void createVulkanImage(VulkanContext* context, u32 width, u32 height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags, VulkanImage* image) {
		VkImageCreateInfo imageInfo { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = width;
		imageInfo.extent.height = height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

		vkCreateImage(context->device.logicalDevice, &imageInfo, nullptr, &image->handle);

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(context->device.logicalDevice, image->handle, &memRequirements);

		VkMemoryAllocateInfo allocInfo { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
		allocInfo.allocationSize = memRequirements.size;

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(context->device.physicalDevice, &memProperties);

		for (uint32_t i = 0; i <memProperties.memoryTypeCount; i++) {
			if ((memRequirements.memoryTypeBits & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				allocInfo.memoryTypeIndex = i;
				break;
			}
		}

		vkAllocateMemory(context->device.logicalDevice, &allocInfo, nullptr, &image->memory);
		vkBindImageMemory(context->device.logicalDevice, image->handle, image->memory, 0);

		createImageView(context, format, image, aspectFlags);
	}

	void destroy(VulkanContext* context, VulkanImage* image) {
		vkDestroyImageView(context->device.logicalDevice, image->view, nullptr);
		vkDestroyImage(context->device.logicalDevice, image->handle, nullptr);
		vkFreeMemory(context->device.logicalDevice, image->memory, nullptr);
	}

	void createImageView(VulkanContext* context, VkFormat format, VulkanImage* image, VkImageAspectFlags aspectFlags) {
		VkImageViewCreateInfo viewInfo { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		viewInfo.image = image->handle;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = format;
		viewInfo.subresourceRange.aspectMask = aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		vkCreateImageView(context->device.logicalDevice, &viewInfo, nullptr, &image->view);
	}
}
