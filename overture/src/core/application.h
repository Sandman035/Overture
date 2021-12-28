#pragma once

#include <defines.h>
#include <platform/window.h>

#include <string>

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
        ~Application();
        
        void onEvent();
        
        void close();
        void run();

        static Application& get() { return *instance; }
        Window& getWindow() { return *window; }
    private:
        b8 running;
        b8 minimized;
        Window *window;
        ApplicationCommandLineArgs args;
        static Application* instance;

        void onWindowClose();
        void onWindowResize();
};

Application* createApplication(ApplicationCommandLineArgs args);