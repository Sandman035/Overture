#pragma once

#include <core/layer.h>

#include <rendering/opengl/opengl_renderer.h>
#include <rendering/opengl/opengl_shader.h>

class TestLayer : public Layer {
    public:
		f32 rotation = 0;

        TestLayer(const std::string& name) :name(name), shader("../test/res/test.glsl") {};
        virtual ~TestLayer() = default;

        void update(f32 deltaTime) override;

        void start() override;
		void end() override;

	private:
		std::string name;
		gl::Shader shader;
		uint32_t VBO, VAO;
		gl::VertexArray vertexArray;
};
