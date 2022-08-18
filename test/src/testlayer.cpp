#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	texture.bind();

	shader.bind();

	gl::drawIndexed(vertexArray, 0);
}

void TestLayer::start() {
	gl::BufferLayout layout = {
		{gl::ShaderDataType::Float3, "aPos"},
		{gl::ShaderDataType::Float3, "aColor"},
		{gl::ShaderDataType::Float2, "aTextCoord"}
	};
	vertexBuffer.setLayout(layout);
	vertexArray.addVertexBuffer(vertexBuffer);

	vertexArray.setIndexBuffer(indexBuffer);

	shader.bind();
	shader.setInt("ourTexture", 0);
}

void TestLayer::end() {
}
