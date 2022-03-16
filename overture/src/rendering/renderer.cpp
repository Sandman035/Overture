#include <rendering/renderer.h>
#include <rendering/renderer.h>

#if PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#endif
#if PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <core/application.h>
#include <platform/window.h>

#include <core/log.h>

#include <fstream>

namespace renderer {
	void init(Init& init) {
		bgfx::PlatformData pd;
#if PLATFORM_LINUX
		pd.ndt = glfwGetX11Display();
		pd.nwh = (void *)glfwGetX11Window(Application::get().getWindow().window);
#endif
		bgfx::Init bgfxInit;
		bgfxInit.type = init.renderer_api;
		bgfxInit.resolution.width = init.window_width;
		bgfxInit.resolution.height = init.window_height;
		bgfxInit.resolution.reset = BGFX_RESET_NONE;
		bgfxInit.platformData = pd;
		bgfx::init(bgfxInit);

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x0b1f3cFF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, init.window_width, init.window_height);

		WindowEventBus::bind(FRAMEBUFFER_RESIZE, renderer::onResize);
	}

	void update() {
		bgfx::touch(0);
		bgfx::frame();
	}

	void shutdown() {
		bgfx::shutdown();
	}

	void onResize(GLFWwindow* window, i32 width, i32 height) {
		DEBUG("Window Resized %d, %d", width, height);
	}

	bgfx::ShaderHandle loadShader(std::string directory, std::string filename) {
		bgfx::ShaderHandle invalid = BGFX_INVALID_HANDLE;

		std::string shaderPath = directory + filename;

		FILE *file = fopen(shaderPath.c_str(), "rb");

		if (!file)
			return invalid;

		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		const bgfx::Memory* mem = bgfx::alloc(fileSize +1);

		fread(mem->data, 1, fileSize, file);
		mem->data[mem->size -1] = '\0';

		fclose(file);

		return bgfx::createShader(mem);
	};
}
