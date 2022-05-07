#pragma once

#include <defines.h>

#include <vulkan/vulkan.h>

namespace vk {
	struct VulkanContext {
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
	};

	struct VertexLayout {};

	struct VertexBuffer {};

	struct IndexBuffer {};

	struct Shader {};

	struct Program {};
}
