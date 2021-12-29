#include <core/application.h>
#include <core/log.h>
#include <core/asserts.h>

Application* Application::instance = nullptr;

Application::Application(const std::string& name, ApplicationCommandLineArgs args) : args(args) {
    ASSERT_MSG(!instance, "Application already exists!");    
    instance = this;
    window = new Window;
    window->init(WindowProperties(name));
}

Application::~Application() {
    //shutdown processes
}

void Application::close() {
    running = false;
}

void Application::run() {
    while (running) {
        //TODO: delta time later

        if (!minimized) {
            for (auto & i : layers) {
                i->update();
            }
        }
        window->onUpdate();

        //temporay fix will be changed later to use the event system
        if (glfwWindowShouldClose(window->window)) {
            close();
        }
    }
    window->shutdown();
}

void Application::pushLayer(Layer * layer) {
    layers.push_back(layer);
    layer->start();
}