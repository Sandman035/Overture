#include "opengl_shader.h"

#include <string.h>
#include <fstream>

#include <core/log.h>
#include <core/asserts.h>

#include <glm/gtc/type_ptr.hpp>

namespace gl {
	namespace utils {
		static GLenum shaderTypeFromString(const std::string& type) {
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;

			ASSERT_MSG(false, "Unknown shader type!");
			return 0;
		}
	}

	std::string Shader::readFile(const std::string& filepath) {
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in) {
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1) {
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			} else {
				ERROR("Could not read from file '%s'", filepath.c_str());
			}
		} else {
			ERROR("Could not open file '%s'", filepath.c_str());
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> Shader::preProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSources;
		
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			ASSERT_MSG(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			ASSERT_MSG(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);

			shaderSources[utils::shaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void Shader::createProgram() {
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, code] : m_openGLSourceCode) {
			GLuint shaderID = glCreateShader(stage);
			shaderIDs.emplace_back(shaderID);
			const char* ccode = code.c_str();
			glShaderSource(shaderID, 1, &ccode, NULL);
			glCompileShader(shaderID);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		
		if (isLinked == GL_FALSE) {
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramPipelineInfoLog(program, maxLength, &maxLength, infoLog.data());
			ERROR("Shader linking failed (%s):\n%s", m_filePath.c_str(), infoLog.data());

			glDeleteProgram(program);
			for (auto id : shaderIDs) {
				glDeleteShader(id);
			}
		}

		for (auto id : shaderIDs) {
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_rendererID = program;
	}

	Shader::Shader(const std::string& filepath) :m_filePath(filepath) {
		std::string source = readFile(filepath);
		m_openGLSourceCode = preProcess(source);

		createProgram();

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind(".");
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_name = filepath.substr(lastSlash, count);
	}

	Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_name(name) {
		m_openGLSourceCode[GL_VERTEX_SHADER] = vertexSrc;
		m_openGLSourceCode[GL_FRAGMENT_SHADER] = fragmentSrc;

		createProgram();
	}

	Shader::~Shader() {
		glDeleteProgram(m_rendererID);
	}

	void Shader::bind() {
		glUseProgram(m_rendererID);
	}

	void Shader::unbind() {
		glUseProgram(0);
	}

	void Shader::setInt(const std::string& name, i32 value) {
		glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), value);
	}

	void Shader::setIntArray(const std::string& name, i32* values, uint32_t count) {
		glUniform1iv(glGetUniformLocation(m_rendererID, name.c_str()), count, values);
	}

	void Shader::setFloat(const std::string& name, f32 value) {
		glUniform1f(glGetUniformLocation(m_rendererID, name.c_str()), value);
	}

	void Shader::setFloat2(const std::string& name, const glm::vec2& value) {
		glUniform2f(glGetUniformLocation(m_rendererID, name.c_str()), value.x, value.y);
	}

	void Shader::setFloat3(const std::string& name, const glm::vec3& value) {
		glUniform3f(glGetUniformLocation(m_rendererID, name.c_str()), value.x, value.y, value.z);
	}

	void Shader::setFloat4(const std::string& name, const glm::vec4& value) {
		glUniform4f(glGetUniformLocation(m_rendererID, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& value) {
		glUniformMatrix4fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
}
