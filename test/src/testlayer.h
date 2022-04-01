#pragma once

#include <core/layer.h>
#include <rendering/renderer.h>

class TestLayer : public Layer {
    public:
		bx::Vec3 position = {0.0f, 0.0f, 0.0f};

        TestLayer();
        virtual ~TestLayer() = default;

        void update() override;

        void start() override;
		void end() override;

	private:
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;
		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;
		bgfx::ProgramHandle program;
};
