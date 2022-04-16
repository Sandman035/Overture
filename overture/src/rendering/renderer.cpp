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
#include <bimg/bimg.h>
#include <bx/bx.h>

#include <core/log.h>

#include <fstream>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <assimp/Importer.hpp>

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

	bgfx::ShaderHandle loadShader(const std::string& directory, const std::string& filename) {
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

	Model loadModel(PosColorVertex vb[], size_t sizeVb, const uint16_t ib[], size_t sizeIb) {
		Model model;

		bgfx::VertexLayout pcvDecl;
		pcvDecl.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
		
		model.vbh = bgfx::createVertexBuffer(bgfx::makeRef(vb, sizeVb), pcvDecl);
		model.ibh = bgfx::createIndexBuffer(bgfx::makeRef(ib, sizeIb));

		return model;
	}

	Model loadModel(const std::string& filepath) {
		Model model;

		bgfx::VertexLayout pcvDecl;
		pcvDecl.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str());

		std::vector<PosColorVertex> verticies;
		std::vector<uint16_t> indices;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				PosColorVertex vertex;

				vertex.x = attrib.vertices[3 * index.vertex_index + 0];
				vertex.y = attrib.vertices[3 * index.vertex_index + 1]; 
				vertex.z = attrib.vertices[3 * index.vertex_index + 2];
				vertex.abgr = 0xffffffff;

				verticies.push_back(vertex);
				indices.push_back(indices.size());
			}
		}

		model.vbh = bgfx::createVertexBuffer(bgfx::makeRef(verticies.data(), verticies.size()), pcvDecl);
		model.ibh = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size()));

		return model;
	}

	void renderModel(Model model) {
		bgfx::setVertexBuffer(0, model.vbh);
		bgfx::setIndexBuffer(model.ibh);

		bgfx::submit(0, model.program);
	}

	void destroy(Model model) {
		bgfx::destroy(model.program);
		bgfx::destroy(model.ibh);
		bgfx::destroy(model.vbh);
	}
}
