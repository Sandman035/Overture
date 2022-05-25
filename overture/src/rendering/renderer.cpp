#include <rendering/renderer.h>

#include <platform/window.h>
#include <core/application.h>
#include "vulkan/vulkan_renderer.h"

#include <core/log.h>

namespace renderer {
	void init(Init& init) {
		vk::initInfo info;

		info.name = init.name;
		info.height = init.window_height;
		info.width = init.window_width;
		
		vk::init(info, &init.context);

		WindowEventBus::bind(FRAMEBUFFER_RESIZE, renderer::onResize);
	}

	void update() {
	}

	void shutdown(vk::VulkanContext* context) {
		vk::shutdown(context);
	}

	void onResize(GLFWwindow* window, i32 width, i32 height) {
		DEBUG("Window Resized %d, %d", width, height);
	}
}
