#pragma once

#include <cstdint>
#include <defines.h>
#include <rendering/renderer_types.h>

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

	bgfx::ShaderHandle loadShader(const std::string& directory, const std::string& filename);

	Model loadModel(PosColorVertex vb[], size_t sizeVb, const uint16_t ib[], size_t sizeIb);
	Model loadModel(const std::string& filepath);

	void renderModel(Model model);

	void destroy(Model model);
}
