#pragma once

#include <defines.h>

#include <string>

#include <GLFW/glfw3.h>

struct WindowProperties {
    u32 width;
    u32 height;

    std::string title;

    WindowProperties(u32 width = 800, u32 height = 600, std::string title = "Overture"): width(width), height(height), title(title) {};
};

class Window {
    public:
        u32 width;
        u32 height;
        GLFWwindow * window;

        void init(const WindowProperties& properties = WindowProperties());
        void shutdown();

        void run();
        void onUpdate();

        //TODO: on error callback, etc.

        void setIcon( /* image */ );
        // more actions similar to set icon
};