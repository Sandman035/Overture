#pragma once

#include <cstdint>
#include <defines.h>
#include "renderer_types.h"
#include "vulkan/vulkan_types.h"

#include <GLFW/glfw3.h>

#include <string>

namespace renderer {
	struct Init {
		uint32_t window_width;
		uint32_t window_height;
		std::string name;
		vk::VulkanContext context;
	};

	void init(Init& info);
	void update();
	void shutdown(vk::VulkanContext* context);

	void onResize(GLFWwindow* window, i32 width, i32 height);
}
