#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>

f32 verticies[] = {
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
};

uint32_t indices[] {
	0, 1, 2 
};

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	shader.bind();

	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TestLayer::start() {
    DEBUG("it works");

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void TestLayer::end() {
	DEBUG("end");
}
