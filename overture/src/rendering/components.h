#pragma once

#include <defines.h>
#include "renderer_types.h"

#include <vector>

#include "opengl/opengl_vertex_array.h"

struct Mesh {
	public:
		Mesh() {}
		Mesh(std::vector<renderer::PosTexColor> verticies, std::vector<uint32_t> indices);

		gl::VertexArray* vertexArray;
	private:
		gl::VertexBuffer* vertexBuffer;
		gl::IndexBuffer* indexBuffer;
};
