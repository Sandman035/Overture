#pragma once

#include <defines.h>
#include <platform/window.h>
#include <core/layer.h>

#include <GLFW/glfw3.h>

#include <string>
#include <list>

struct ApplicationCommandLineArgs {
	int Count = 0;
	char** Args = nullptr;

	const char* operator[](int index) const
	{
		return Args[index];
	}
};

struct ApplicationInfo {
	i32 width = 600;
	i32 height = 800;
	std::string name = "Overture";
};

class Application {
    public:
        Application(ApplicationInfo info, ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
        virtual ~Application();
        
        void onEvent();
        
        void close();
        void run();

        void pushLayer(Layer * layer);
		void removeLayer(const std::string & name);

        static Application& get() { return *instance; }
        OvertureWindow& getWindow() { return *window; }

		b8 isResized() { return resized; }
		void setResized(b8 value) { resized = value; }

    private:
        b8 running = true;
        b8 minimized = false;
		b8 resized;
		f32 deltaTime;

        OvertureWindow *window;
        ApplicationCommandLineArgs args;
        static Application* instance;
        std::list<Layer*> layers;
};

void onWindowResize(GLFWwindow* window, i32 width, i32 height); //will be needed later for rendering

Application* createApplication(ApplicationCommandLineArgs args);
