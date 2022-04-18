#pragma once

#include <defines.h>
#include <rendering/vulkan/vulkan_types.h>

namespace vk {
	void init();
	void shutdown();

	void frame();

	VertexBuffer createVertexBuffer(const void* mem, const VertexLayout &layout);
	IndexBuffer createIndexBuffer(const void* mem);
	Shader createShader(const void* mem);
	Program createProgram(Shader vertex, Shader fragment);

	void setVertexBuffer(VertexBuffer vb);
	void setIndexBuffer(IndexBuffer ib);
	void submit(Program program);

	void setUniform();

	void destroy(/* insert any object needed to be destroyed */);
}
