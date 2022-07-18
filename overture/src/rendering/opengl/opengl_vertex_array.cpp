#include "opengl_vertex_array.h"

#include <glad/glad.h>

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
		glCreateVertexArrays(1, &m_rendererID);
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
		vertexBuffer.bind();

		const auto& layout = vertexBuffer.getLayout();
		for (const auto& element : layout) {
			switch (element.m_type) {
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4: {
					glEnableVertexAttribArray(m_vertexBufferIndex);
					glVertexAttribPointer(m_vertexBufferIndex,
						element.GetComponentCount(),
						shaderDataTypeToOpenGLBaseType(element.m_type),
						element.m_normalized ? GL_TRUE : GL_FALSE,
						layout.getStride(),
						(const void*)element.m_offset);
					m_vertexBufferIndex++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool: {
					glEnableVertexAttribArray(m_vertexBufferIndex);
					glVertexAttribIPointer(m_vertexBufferIndex,
						element.GetComponentCount(),
						shaderDataTypeToOpenGLBaseType(element.m_type),
						layout.getStride(),
						(const void*)element.m_offset);
					m_vertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4: {
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++) {
						glEnableVertexAttribArray(m_vertexBufferIndex);
						glVertexAttribPointer(m_vertexBufferIndex,
							count,
							shaderDataTypeToOpenGLBaseType(element.m_type),
							element.m_normalized ? GL_TRUE : GL_FALSE,
							layout.getStride(),
							(const void*)(element.m_offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_vertexBufferIndex, 1);
						m_vertexBufferIndex++;
					}
					break;
				}
				default:
					break;
			}
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::setIndexBuffer(IndexBuffer& indexBuffer) {
		glBindVertexArray(m_rendererID);
		indexBuffer.bind();

		m_indexBuffer = indexBuffer;
	}
}
