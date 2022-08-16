#include "opengl_renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/log.h>

namespace gl {
	void DebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         FATAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: TRACE(message); return;
		}
	}

	void init() {
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

#if RELEASE == 0
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, nullptr);
		
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void setClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void drawIndexed(VertexArray& vertexArray, uint32_t indexCount) {
		vertexArray.bind();

		uint32_t count = indexCount ? indexCount : vertexArray.getIndexBuffer().getCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

	}

	void drawLines(VertexArray& vertexArray, uint32_t vertexCount) {
		vertexArray.bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
	
	void setLineWidth(f32 width) {
		glLineWidth(width);
	}
}
