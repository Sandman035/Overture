#include <platform/window.h>

#include <core/asserts.h>
#include <core/log.h>

void Window::init(const WindowProperties& properties) {
    ASSERT_MSG(glfwInit(), "glfw failed to initialize");

    window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, nullptr);

    ASSERT_MSG(window, "failed to create window");

    glfwMakeContextCurrent(window);
}

void Window::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::run() {
    while (!glfwWindowShouldClose(window))
    {
        onUpdate();
    }

    shutdown();
}