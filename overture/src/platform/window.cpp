#include <GLFW/glfw3.h>
#include <platform/window.h>

#include <core/asserts.h>
#include <core/log.h>

void Window::init(const WindowProperties& properties) {
    ASSERT_MSG(glfwInit(), "glfw failed to initialize");
	
	//TODO: make this part allow different apis
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	glfwSetErrorCallback(onErrorCallback);

    window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, nullptr);

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
