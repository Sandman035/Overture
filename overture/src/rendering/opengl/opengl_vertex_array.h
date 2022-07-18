#pragma once

#include <defines.h>

#include <cstdint>
#include <vector>

#include "opengl_buffers.h"

namespace gl {
	class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			void bind();
			void unbind();

			void addVertexBuffer(VertexBuffer& vertexBuffer);
			void setIndexBuffer(IndexBuffer& vertexBuffer);

			const std::vector<VertexBuffer>& getVertexBuffers() const { return m_vertexBuffers; }
			const IndexBuffer& getIndexBuffer() const { return m_indexBuffer; }

		private:
			uint32_t m_rendererID;
			uint32_t m_vertexBufferIndex = 0;
			std::vector<VertexBuffer> m_vertexBuffers;
			IndexBuffer m_indexBuffer;
	};
}
