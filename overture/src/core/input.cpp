#include <core/input.h>

#include <core/application.h>
#include <GLFW/glfw3.h>

b8 Input::isKeyPressed(const keyCode code) {
    GLFWwindow* window = Application::get().getWindow().window;
    auto state = glfwGetKey(window, static_cast<int32_t>(code));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

b8 Input::isMouseButtonPressed(const mouseCode code) {
    GLFWwindow* window = Application::get().getWindow().window;
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(code));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

Vector2 Input::getMousePos() {
    GLFWwindow* window = Application::get().getWindow().window;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Vector2((float)x, (float)y);
}

float Input::getMouseX() {
    return getMousePos().x;
}

float Input::getMouseY() {
    return getMousePos().y;
}