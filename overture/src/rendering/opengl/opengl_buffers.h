#pragma once

#include <defines.h>

#include <cstdint>
#include <string>
#include <vector>

namespace gl {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4
	};

	uint32_t ShaderDataTypeSize(ShaderDataType type);

	struct BufferElement {
		std::string m_name;
		ShaderDataType m_type;
		uint32_t m_size;
		size_t m_offset;
		b8 m_normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : m_name(name), m_type(type), m_size(ShaderDataTypeSize(type)), m_offset(0), m_normalized(normalized) {}

		uint32_t GetComponentCount() const;
	};

	class BufferLayout {
		public:
			BufferLayout() {}

			BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements) {
				calculateOffsetsAndStride();
			}

			uint32_t getStride() const { return m_stride; }
			const std::vector<BufferElement>& getElements() const { return m_elements; }

			std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
			std::vector<BufferElement>::iterator end() { return m_elements.end(); }
			std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

		private:
			void calculateOffsetsAndStride();

			std::vector<BufferElement> m_elements;
			uint32_t m_stride = 0;
	};

	class VertexBuffer {
		public:
			VertexBuffer(f32* verticies, uint32_t size);
			~VertexBuffer();

			void bind();
			void unbind();

			void setData(const void* data, uint32_t size);

			BufferLayout& getLayout() { return m_layout; }
			void setLayout(const BufferLayout& layout) { m_layout = layout; }

		private:
			uint32_t m_rendererID;
			BufferLayout m_layout;
	};

	class IndexBuffer {
		public:
			IndexBuffer() {}
			IndexBuffer(uint32_t* indices, uint32_t count);
			~IndexBuffer();

			void bind();
			void unbind();

			uint32_t getCount() const { return m_count; }

		private:
			uint32_t m_count;
			uint32_t m_rendererID;
	};
}
