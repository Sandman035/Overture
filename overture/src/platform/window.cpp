#include <GLFW/glfw3.h>
#include <platform/window.h>

#include <core/asserts.h>
#include <core/log.h>

framebufferResizeFunctionList WindowEventBus::framebufferResizeList = {};

void WindowEventBus::bind(WindowEvents event, void(*func)(GLFWwindow*, i32, i32)) {
	switch (event) {
		case FRAMEBUFFER_RESIZE:
			framebufferResizeList.push_back(func);
			break;
		default:
			break;
	}
}

void WindowEventBus::call(WindowEvents event, GLFWwindow* window, i32 width, i32 height) {
	switch (event) {
		case FRAMEBUFFER_RESIZE:
			for (auto & i : framebufferResizeList) {
				i(window, width, height);
			}
			break;
		default:
			break;
	}
}

void OvertureWindow::init(const WindowProperties& properties) {
    ASSERT_MSG(glfwInit(), "glfw failed to initialize");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if RELEASE == 0
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	glfwSetErrorCallback(onErrorCallback);

    window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, nullptr);
	width = properties.width;
	height = properties.height;
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, onResize);
    ASSERT_MSG(window, "failed to create window");
}

void OvertureWindow::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void OvertureWindow::onUpdate() {
	glfwSwapBuffers(window);
    glfwPollEvents();
}

void OvertureWindow::onErrorCallback(i32 code, const char *description) {
	ERROR("GLFW [%d]: %s", code, description);
}

void OvertureWindow::onResize(GLFWwindow* window, i32 width, i32 height) {
	WindowEventBus::call(FRAMEBUFFER_RESIZE, window, width, height);
}
