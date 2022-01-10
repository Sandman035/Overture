#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>

TestLayer::TestLayer() {
    //nothing		
}

void TestLayer::update() {
    if(Input::isKeyPressed(W)) {
        INFO("hello");
    }

    if(Input::isKeyPressed(Escape)) {
		renderer.shutdown();
        Application::get().close();        
    }
}

void TestLayer::start() {
    DEBUG("it works");
	renderer.init();
}
