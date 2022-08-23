#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>

struct TestComponent {
	f32 thing;
};

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	texture->bind();

	shader->bind();

	gl::drawIndexed(vertexArray, 0);
}

void TestLayer::start() {
	shader = new gl::Shader("../test/res/test.glsl");
	vertexBuffer = new gl::VertexBuffer(verticies, sizeof(verticies));
	indexBuffer = new gl::IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));
	texture = new gl::Texture2D("../test/res/wall.jpg");

	gl::BufferLayout layout = {
		{gl::ShaderDataType::Float3, "aPos"},
		{gl::ShaderDataType::Float3, "aColor"},
		{gl::ShaderDataType::Float2, "aTextCoord"}
	};
	vertexBuffer->setLayout(layout);
	vertexArray.addVertexBuffer(*vertexBuffer);

	vertexArray.setIndexBuffer(*indexBuffer);

	shader->bind();
	shader->setInt("ourTexture", 0);

	scene.init();
	scene.registerComponent<TestComponent>();

	ecs::Entity testEntity = scene.createEntity();

	scene.addComponent<TestComponent>(testEntity, { 0.1f });

	DEBUG("%f", scene.getComponent<TestComponent>(testEntity).thing);
}

void TestLayer::end() {
}
