#pragma once

#include <defines.h>

#include <glad/glad.h>

#include <cstdint>
#include <string>

namespace gl {
	class Texture2D {
		public:
			Texture2D(uint32_t width, uint32_t height);
			Texture2D(const std::string& path);
			~Texture2D();

			uint32_t getWidth() { return m_width; }
			uint32_t getHeight() { return m_height; }
			uint32_t getRendererID() { return m_rendererID; }
			const std::string& getPath() { return m_path; }

			void setData(void* data, uint32_t size);

			void bind(uint32_t slot = 0);

			bool isLoaded() { return m_isLoaded; }

		private:
			std::string m_path;
			bool m_isLoaded = false;
			uint32_t m_width, m_height;
			uint32_t m_rendererID;
			GLenum m_internalFormat, m_dataFormat;
	};
}
