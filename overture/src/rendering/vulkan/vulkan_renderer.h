#pragma once

#include <defines.h>

#include "vulkan_types.h"
#include "vulkan_helpers.h"

#include <vulkan/vulkan.h>

namespace vk {
	void init(const initInfo& info, VulkanContext* context);
	void shutdown(VulkanContext* context);

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
