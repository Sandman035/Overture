#include "vulkan_renderer.h"

#include <core/log.h>
#include <core/asserts.h>
#include <core/application.h>

#include "vulkan_device.h"
#include "vulkan_swapchain.h"

#include <GLFW/glfw3.h>

namespace vk {
	void init(const initInfo& info, VulkanContext* context) {
		b8 validationLayerSupported = checkValidationLayerSupport();

		VkApplicationInfo appinfo{};
		appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appinfo.pApplicationName = info.name.c_str();
		appinfo.pEngineName = "Overture";
		appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appinfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
		appinfo.apiVersion = VK_API_VERSION_1_3;

		VkInstanceCreateInfo instanceInfo{};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appinfo;

		auto extentions = getRequiredExtentions();
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extentions.size());
		instanceInfo.ppEnabledExtensionNames = extentions.data();

#if RELEASE == 0
		if (validationLayerSupported) {
			instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			instanceInfo.ppEnabledLayerNames = validationLayers.data();
		} else {
			instanceInfo.enabledLayerCount = 0;
		}
#else
		instanceInfo.enabledLayerCount = 0;
#endif

		if (vkCreateInstance(&instanceInfo, nullptr, &context->instance) != VK_SUCCESS) {
			ERROR("failed to create instance");
		}
		INFO("vulkan instance created");

#if RELEASE == 0
		INFO("creating vulkan debuger");
		if (validationLayerSupported) {
			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;	
			debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debugCreateInfo.pfnUserCallback = debugCallback;
			debugCreateInfo.pNext = NULL;
			debugCreateInfo.flags = 0;

			auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(context->instance, "vkCreateDebugUtilsMessengerEXT");
			func(context->instance, &debugCreateInfo, nullptr, &context->debugMessenger);
		}
#endif
		INFO("creating vulkan surface");
		if (glfwCreateWindowSurface(context->instance, Application::get().getWindow().window, nullptr, &context->surface) != VK_SUCCESS) {
			ERROR("failed to create surface");
		}
		INFO("vulkan surface created");

		createDevice(context);

		createSwapchain(context, info.width, info.height, &context->swapchain);
	}

	void shutdown(VulkanContext* context) {
		INFO("Starting renderer shutdown");

		INFO("Destroying swapchain");
		//TODO: fix core being dumped
		//destroySwapchain(context, &context->swapchain);

		INFO("Destroying device");
		destroyDevice(context);

		INFO("Destroying debugMessenger");
		if (context->debugMessenger != VK_NULL_HANDLE) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(context->instance, "vkDestroyDebugUtilsMessengerEXT");
			if (func != nullptr) {
				func(context->instance, context->debugMessenger, nullptr);
			}
		}

		INFO("Destroying vulkan surface");
		//TODO: fix core being dumped
		//vkDestroySurfaceKHR(context->instance, context->surface, nullptr);

		INFO("Destroying vulkan instance");
		vkDestroyInstance(context->instance, nullptr);
	}
}
