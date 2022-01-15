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

void Window::init(const WindowProperties& properties) {
    ASSERT_MSG(glfwInit(), "glfw failed to initialize");
	
	//TODO: make this part allow different apis
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	glfwSetErrorCallback(onErrorCallback);

    window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, nullptr);

	glfwSetFramebufferSizeCallback(window, onResize);
    ASSERT_MSG(window, "failed to create window");
}

void Window::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::onUpdate() {
    glfwPollEvents();
}

void Window::run() {
    while (!glfwWindowShouldClose(window))
    {
        onUpdate();
    }

    shutdown();
}

void Window::onErrorCallback(i32 code, const char *description) {
	ERROR("GLFW [%d]: %s", code, description);
}

void Window::onResize(GLFWwindow* window, i32 width, i32 height) {
	WindowEventBus::call(FRAMEBUFFER_RESIZE, window, width, height);
}
