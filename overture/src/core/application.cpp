#include <core/application.h>
#include <core/log.h>
#include <core/asserts.h>
#include <ctime>

#include <rendering/renderer.h>

Application* Application::instance = nullptr;

Application::Application(ApplicationInfo info, ApplicationCommandLineArgs args) : args(args) {
    ASSERT_MSG(!instance, "Application already exists!");    
    instance = this;
    window = new OvertureWindow;

	WindowProperties properties;
	properties.height = info.height;
	properties.width = info.width;
	properties.title = info.name;

    window->init(properties);

	renderer::Init initInfo;
	initInfo.renderer_api = bgfx::RendererType::Vulkan;
	initInfo.window_height = window->height;
	initInfo.window_width = window->width;

	renderer::init(initInfo);
}

Application::~Application() {
    //shutdown processes
}

void Application::close() {
    running = false;
}

void Application::run() {
    while (running) {
		//TODO: change to a more precise clock std::chrono::high_resolution_clock
		const clock_t begin_time = clock();

        if (!minimized) {
            for (auto & i : layers) {
                i->update(deltaTime);
            }
        }
        window->onUpdate();

		renderer::update();

        //temporay fix will be changed later to use the event system
        if (glfwWindowShouldClose(window->window)) {
            close();
        }
		deltaTime = float(clock() - begin_time ) / CLOCKS_PER_SEC;
    }

	for (auto & i : layers) {
		i->end();
	}
    window->shutdown();
	renderer::shutdown();
}

void Application::pushLayer(Layer * layer) {
    layers.push_back(layer);
    layer->start();
}
