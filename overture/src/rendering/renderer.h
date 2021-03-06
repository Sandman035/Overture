#pragma once

#include <cstdint>
#include <defines.h>
#include "renderer_types.h"

#include <GLFW/glfw3.h>

#include <string>

namespace renderer {
	struct Init {
		uint32_t window_width;
		uint32_t window_height;
	};

	void init(Init& info);
	void update();
	void shutdown();

	void onResize(GLFWwindow* window, i32 width, i32 height);
}
