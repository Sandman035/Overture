#pragma once

#include <defines.h>

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace gl {
	class Shader {
		public:
			Shader(const std::string& filepath);
			Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
			~Shader();

			void bind();
			void unbind();

			void setInt(const std::string& name, i32 value);
			void setIntArray(const std::string& name, i32* values, uint32_t count);
			void setFloat(const std::string& name, f32 value);
			void setFloat2(const std::string& name, const glm::vec2& value);
			void setFloat3(const std::string& name, const glm::vec3& value);
			void setFloat4(const std::string& name, const glm::vec4& value);
			void setMat4(const std::string& name, const glm::mat4& value);

			const std::string& getName() const { return m_name; }

		private:
			uint32_t m_rendererID;
			std::string m_filePath;
			std::string m_name;

			std::unordered_map<GLenum, std::string> m_openGLSourceCode;

			std::string readFile(const std::string& filepath);
			std::unordered_map<GLenum, std::string> preProcess(const std::string& source);

			void createProgram();
			void reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
	};
}
