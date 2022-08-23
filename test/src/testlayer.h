#pragma once

#include <core/layer.h>

#include <defines.h>
#include <rendering/opengl/opengl_renderer.h>
#include <rendering/opengl/opengl_textures.h>

#include <systems/ecs_scene.h>

static f32 verticies[] = {
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.5f, 1.0f
};

static uint32_t indices[] {
	0, 1, 2 
};

class TestLayer : public Layer {
    public:
		f32 rotation = 0;

        TestLayer(const std::string& name) :name(name)/*, shader("../test/res/test.glsl"), vertexBuffer(verticies, sizeof(verticies)), indexBuffer(indices, sizeof(indices) / sizeof(uint32_t)), texture("../test/res/wall.jpg")*/ {};
        virtual ~TestLayer() = default;

        void update(f32 deltaTime) override;

        void start() override;
		void end() override;

	private:
		std::string name;
		//gl::Shader shader;
		//gl::VertexArray vertexArray;
		//gl::VertexBuffer vertexBuffer;
		//gl::IndexBuffer indexBuffer;
		//gl::Texture2D texture;
		gl::Shader* shader;
		gl::VertexArray vertexArray;
		gl::VertexBuffer* vertexBuffer;
		gl::IndexBuffer* indexBuffer;
		gl::Texture2D* texture;
		ecs::Scene scene;
};
