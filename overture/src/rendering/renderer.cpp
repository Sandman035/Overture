#include <rendering/renderer.h>

#include <platform/window.h>
#include <core/application.h>

#include <core/log.h>

#include "opengl/opengl_renderer.h"

namespace renderer {
	void init(Init& init) {
		gl::init();
		gl::setViewport(0, 0, init.window_width, init.window_height);

		gl::setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		WindowEventBus::bind(FRAMEBUFFER_RESIZE, renderer::onResize);
	}

	void update() {
		gl::clear();
	}

	void shutdown() {
	}

	void onResize(GLFWwindow* window, i32 width, i32 height) {
		gl::setViewport(0, 0, width, height);
	}
}
