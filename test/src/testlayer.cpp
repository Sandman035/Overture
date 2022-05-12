#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>
#include <rendering/renderer.h>

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }
}

void TestLayer::start() {
    DEBUG("it works");
}

void TestLayer::end() {
	DEBUG("end");
}
