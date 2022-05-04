#include "vulkan_renderer.h"

#include <core/log.h>
#include <core/asserts.h>

namespace vk {
	void init(const initInfo& info, VulkanContext* context) {
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

		//TODO: add validation layers on non-release builds
		instanceInfo.enabledLayerCount = 0;

		vkCreateInstance(&instanceInfo, nullptr, &context->instance);
	}
}
