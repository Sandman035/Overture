#pragma once

#include <core/layer.h>
#include <rendering/renderer.h>

class TestLayer : public Layer {
    public:
		bx::Vec3 position = {0.0f, 0.0f, 0.0f};
		f32 rotation = 0;

        TestLayer(const std::string& name) :name(name) {};
        virtual ~TestLayer() = default;

        void update(f32 deltaTime) override;

        void start() override;
		void end() override;

	private:
		std::string name;

		renderer::Model model;

		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;
};
