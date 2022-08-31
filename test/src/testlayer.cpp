#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>

#include <rendering/components.h>

struct TestComponent {
	f32 thing;
};

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	texture->bind();

	shader->bind();

	if (scene.hasComponent<Mesh>(testEntity)) {
		gl::drawIndexed(*scene.getComponent<Mesh>(testEntity).vertexArray, 0);
	}
}

void TestLayer::start() {
	scene.init();
	scene.registerComponent<TestComponent>();
	scene.registerComponent<Mesh>();

	testEntity = scene.createEntity();

	scene.addComponent<TestComponent>(testEntity, { 0.1f });
	scene.addComponent<Mesh>(testEntity, {verticies, indices});

	texture = new gl::Texture2D("../test/res/wall.jpg");
	shader = new gl::Shader("../test/res/test.glsl");

	shader->bind();
	shader->setInt("ourTexture", 0);

	DEBUG("%f", scene.getComponent<TestComponent>(testEntity).thing);
}

void TestLayer::end() {
}
