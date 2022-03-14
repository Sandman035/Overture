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
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glfwSetErrorCallback(onErrorCallback);

    window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, nullptr);
	width = properties.width;
	height = properties.height;

	glfwSetFramebufferSizeCallback(window, onResize);
    ASSERT_MSG(window, "failed to create window");
}

void OvertureWindow::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void OvertureWindow::onUpdate() {
    glfwPollEvents();
}

void OvertureWindow::run() {
    while (!glfwWindowShouldClose(window))
    {
        onUpdate();
    }

    shutdown();
}

void OvertureWindow::onErrorCallback(i32 code, const char *description) {
	ERROR("GLFW [%d]: %s", code, description);
}

void OvertureWindow::onResize(GLFWwindow* window, i32 width, i32 height) {
	WindowEventBus::call(FRAMEBUFFER_RESIZE, window, width, height);
}
