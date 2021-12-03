#pragma once

#include <defines.h>

#include <string>

struct WindowProperties {
    u32 width;
    u32 height;

    std::string title;

    WindowProperties(u32 width = 800, u32 height = 600, std::string title = "Overture"): width(width), height(height), title(title) {};
};

class Window {
    public:
        static Window create(const WindowProperties& properties = WindowProperties());
};