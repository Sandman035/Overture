#include "opengl_vertex_array.h"

#include <glad/glad.h>
#include <core/log.h>

namespace gl {
	GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type) {
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			default: 					   return 0;
		}
	}

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_rendererID);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void VertexArray::bind() {
		glBindVertexArray(m_rendererID);
	}

	void VertexArray::unbind() {
		glBindVertexArray(0);
	}

	void VertexArray::addVertexBuffer(VertexBuffer& vertexBuffer) {
		glBindVertexArray(m_rendererID);
		vertexBuffer.setData();

		const auto& layout = vertexBuffer.getLayout();
		for (const auto& element : layout) {
			DEBUG("%d", m_vertexBufferIndex);
			glVertexAttribPointer(m_vertexBufferIndex,
				element.GetComponentCount(),
				shaderDataTypeToOpenGLBaseType(element.m_type),
				element.m_normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.m_offset);
			glEnableVertexAttribArray(m_vertexBufferIndex);
			m_vertexBufferIndex++;
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::setIndexBuffer(IndexBuffer& indexBuffer) {
		glBindVertexArray(m_rendererID);
		indexBuffer.bind();

		m_indexBuffer = indexBuffer;
	}
}
