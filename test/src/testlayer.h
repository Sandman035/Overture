#pragma once

#include <core/layer.h>

#include <defines.h>
#include <rendering/opengl/opengl_renderer.h>
#include <rendering/opengl/opengl_textures.h>

#include <systems/ecs_scene.h>

#include <rendering/renderer_types.h>


static std::vector<renderer::PosTexColor> verticies = {
	{{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
	{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	{{0.0f,  0.5f, 0.0f},  {0.0f, 0.0f}, {1.0f, 0.5f, 1.0f}}
};

static std::vector<uint32_t> indices {
	0, 1, 2 
};

class TestLayer : public Layer {
    public:
		f32 rotation = 0;

        TestLayer(const std::string& name) :name(name) {};
        virtual ~TestLayer() = default;

        void update(f32 deltaTime) override;

        void start() override;
		void end() override;

	private:
		std::string name;
		gl::Shader* shader;
		gl::Texture2D* texture;
		ecs::Scene scene;
		ecs::Entity testEntity;
};
