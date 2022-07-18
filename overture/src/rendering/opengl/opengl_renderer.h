#pragma once 

#include <defines.h>

#include <cstdint>

#include <glm/glm.hpp>
#include "opengl_vertex_array.h"

namespace gl {
	void init();
	void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	
	void setClearColor(const glm::vec4& color);
	void clear();

	void drawIndexed(VertexArray& vertexArray, uint32_t indexCount);
	void drawLines(VertexArray& vertexArray, uint32_t vertexCount);
	
	void setLineWidth(f32 width);
}
