#include "vulkan_swapchain.h"

#include <algorithm>

namespace vk {
	void create(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain);
	void destroy(VulkanContext* context, VulkanSwapchain* swapchain);
	
	void createSwapchain(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain) {
		create(context, width, height, swapchain);
	}

	void recreateSwapchain(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain) {
		destroy(context, swapchain);
		create(context, width, height, swapchain);
	}

	void destroySwapchain(VulkanContext* context, VulkanSwapchain* swapchain) {
		destroy(context, swapchain);
	}

	void create(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain) {
		VkExtent2D swapchainExtent = {width, height};

		b8 found = false;
		for (u32 i = 0; i < context->device.swapchainSupport.formatCount; i++) {
			VkSurfaceFormatKHR format =  context->device.swapchainSupport.formats.at(i);

			if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
				swapchain->imageFormat = format;
				found = true;
				break;
			}

			if (!found) {
				swapchain->imageFormat = context->device.swapchainSupport.formats.at(0);
			}
		}

		VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
		for (u32 i = 0; i < context->device.swapchainSupport.presentModeCount; i++) {
			VkPresentModeKHR mode = context->device.swapchainSupport.presentModes.at(i);
			if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
				presentMode = mode;
				break;
			}
		}

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context->device.physicalDevice, context->surface, &context->device.swapchainSupport.capabilities);

		if (context->device.swapchainSupport.capabilities.currentExtent.width != UINT32_MAX) {
			swapchainExtent = context->device.swapchainSupport.capabilities.currentExtent;
		}

		VkExtent2D min = context->device.swapchainSupport.capabilities.minImageExtent;
		VkExtent2D max = context->device.swapchainSupport.capabilities.maxImageExtent;
		swapchainExtent.width = std::clamp(swapchainExtent.width, min.width, max.width);
		swapchainExtent.height = std::clamp(swapchainExtent.height, min.height, max.height);

		u32 imageCount = context->device.swapchainSupport.capabilities.minImageCount + 1;
		if (context->device.swapchainSupport.capabilities.maxImageCount > 0 && imageCount > context->device.swapchainSupport.capabilities.maxImageCount) {
			imageCount = context->device.swapchainSupport.capabilities.maxImageCount;
		}

		swapchain->maxFrames = imageCount - 1;

		VkSwapchainCreateInfoKHR swapchainCreateInfo = {VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
		swapchainCreateInfo.surface = context->surface;
		swapchainCreateInfo.minImageCount = imageCount;
		swapchainCreateInfo.imageFormat = swapchain->imageFormat.format;
		swapchainCreateInfo.imageColorSpace = swapchain->imageFormat.colorSpace;
		swapchainCreateInfo.imageExtent = swapchainExtent;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (context->device.graphicsFamily != context->device.presentFamily) {
			u32 queueFamilyIndices[] = { (u32)context->device.graphicsFamily, (u32)context->device.presentFamily};
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			swapchainCreateInfo.queueFamilyIndexCount = 2;
			swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
		} else {
			swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			swapchainCreateInfo.queueFamilyIndexCount = 0;
			swapchainCreateInfo.pQueueFamilyIndices = 0;
		}

		swapchainCreateInfo.preTransform = context->device.swapchainSupport.capabilities.currentTransform;
		swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.presentMode = presentMode;
		swapchainCreateInfo.clipped = VK_TRUE;
		swapchainCreateInfo.oldSwapchain = 0;

		vkCreateSwapchainKHR(context->device.logicalDevice, &swapchainCreateInfo, nullptr, &swapchain->handle);
	}

	void destroy(VulkanContext* context, VulkanSwapchain* swapchain) {
	}
}
