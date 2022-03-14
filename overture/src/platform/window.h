#pragma once

#include <defines.h>

#include <string>

#include <GLFW/glfw3.h>
#include <list>

enum WindowEvents {
	FRAMEBUFFER_RESIZE,
};

typedef std::list<void (*)(GLFWwindow*, i32, i32)> framebufferResizeFunctionList;

class WindowEventBus {
	public:
		static void bind(WindowEvents event, void(*func)(GLFWwindow*, i32, i32));
		static void call(WindowEvents event, GLFWwindow* window, i32 width, i32 height);
	private:
		static framebufferResizeFunctionList framebufferResizeList;
};

struct WindowProperties {
    u32 width;
    u32 height;

    std::string title;

    WindowProperties(const std::string& title = "Overture", u32 width = 800, u32 height = 600): width(width), height(height), title(title) {};
};

class OvertureWindow {
    public:
        u32 width;
        u32 height;
        GLFWwindow * window;

        void init(const WindowProperties& properties = WindowProperties());
        void shutdown();

        void run();
        void onUpdate();

		static void onResize(GLFWwindow* window, i32 width, i32 height);

		static void onErrorCallback(i32 code, const char* description);

        //void setIcon( /* image */ );
        // more actions similar to set icon
};
