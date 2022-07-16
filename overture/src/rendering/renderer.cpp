#include <rendering/renderer.h>

#include <platform/window.h>
#include <core/application.h>

#include <core/log.h>

namespace renderer {
	void init(Init& init) {

		WindowEventBus::bind(FRAMEBUFFER_RESIZE, renderer::onResize);
	}

	void update() {
	}

	void shutdown() {
	}

	void onResize(GLFWwindow* window, i32 width, i32 height) {
		DEBUG("Window Resized %d, %d", width, height);
	}
}
