#include "vulkan_device.h"

#include "vulkan_helpers.h"

#include <vector>
#include <optional>
#include <set>

namespace vk {
	void createDevice(VulkanContext* context) {
		selecPhysicalDevice(context);
	}

	void selecPhysicalDevice(VulkanContext* context) {
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(context->instance, &deviceCount, nullptr);

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(context->instance, &deviceCount, devices.data());

		for (const auto& device : devices) {
			if (isDeviceSuitable(device, context)) {
				context->device.physicalDevice = device;
				break;
			}
		}
	}

	b8 isDeviceSuitable(VkPhysicalDevice device, VulkanContext* context) {
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		std::optional<uint32_t> graphicsFamily, presentFamily;

		i32 i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				graphicsFamily = i;

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, context->surface, &presentSupport);

			if (presentSupport)
				presentFamily = i;

			if (graphicsFamily.has_value() && presentFamily.has_value())
				break;

			i++;
		}

		uint32_t extentionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extentionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtentions(extentionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extentionCount, availableExtentions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extention : availableExtentions) {
			requiredExtensions.erase(extention.extensionName);
		}

		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, context->surface, &formatCount, nullptr);

		if (formatCount != 0) {
			formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, context->surface, &formatCount, formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, context->surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, context->surface, &presentModeCount, presentModes.data());
		}

		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

		return graphicsFamily.has_value() && presentFamily.has_value() && requiredExtensions.empty() && !formats.empty() && !presentModes.empty() && supportedFeatures.samplerAnisotropy;
	}
};
