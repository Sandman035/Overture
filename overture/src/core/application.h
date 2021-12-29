#pragma once

#include <defines.h>
#include <platform/window.h>
#include <core/layer.h>

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

class Application {
    public:
        Application(const std::string& name = "Overture", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
        virtual ~Application();
        
        void onEvent();
        
        void close();
        void run();

        void pushLayer(Layer * layer);

        static Application& get() { return *instance; }
        Window& getWindow() { return *window; }
    private:
        b8 running = true;
        b8 minimized = false;
        Window *window;
        ApplicationCommandLineArgs args;
        static Application* instance;
        std::list<Layer*> layers;
        void onWindowResize(); //will be needed later for rendering
};

Application* createApplication(ApplicationCommandLineArgs args);