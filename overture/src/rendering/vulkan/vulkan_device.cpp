#include "vulkan_device.h"

#include "vulkan_helpers.h"
#include <core/log.h>

#include <vector>
#include <optional>
#include <set>

namespace vk {
	void createDevice(VulkanContext* context) {
		selecPhysicalDevice(context);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {context->device.graphicsFamily, context->device.presentFamily};

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};
		deviceFeatures.samplerAnisotropy = VK_TRUE;

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

#if RELEASE == 0
		if (checkValidationLayerSupport()) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		} else {
			createInfo.enabledLayerCount = 0;
		}
#else
		createInfo.enabledLayerCount = 0;
#endif
		if (vkCreateDevice(context->device.physicalDevice, &createInfo, nullptr, &context->device.logicalDevice) != VK_SUCCESS) {
			ERROR("failed to create vulkan device");
		}

		vkGetDeviceQueue(context->device.logicalDevice, context->device.graphicsFamily, 0, &context->device.graphicsQueue);
		vkGetDeviceQueue(context->device.logicalDevice, context->device.presentFamily, 0, &context->device.presentQueue);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = context->device.graphicsFamily;
		poolInfo.flags = 0;
		if (vkCreateCommandPool(context->device.logicalDevice, &poolInfo, nullptr, &context->device.commandPool) != VK_SUCCESS) {
			ERROR("failed to create command pool");
		}
	}

	void destroyDevice(VulkanContext* context) {
		context->device.graphicsQueue = 0;
		context->device.presentQueue = 0;

		INFO("Destroying command pool");
		vkDestroyCommandPool(context->device.logicalDevice, context->device.commandPool, nullptr);
		
		INFO("Destroying logical device");
		vkDestroyDevice(context->device.logicalDevice, nullptr);
		context->device.logicalDevice = 0;

		INFO("Releasing physical device resources");
		context->device.physicalDevice = 0;
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

		context->device.graphicsFamily = graphicsFamily.value();
		context->device.presentFamily = presentFamily.value();

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
