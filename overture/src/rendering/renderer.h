#pragma once

#include <cstdint>
#include <defines.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <GLFW/glfw3.h>

#include <string>

namespace renderer {
	struct Init {
		uint32_t window_width;
		uint32_t window_height;
		bgfx::RendererType::Enum renderer_api = bgfx::RendererType::Count;
		
	};

	void init(Init& info);
	void update();
	void shutdown();

	void onResize(GLFWwindow* window, i32 width, i32 height);

	bgfx::ShaderHandle loadShader(std::string directory, std::string filename);
}
