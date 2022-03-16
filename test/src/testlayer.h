#pragma once

#include <core/layer.h>
#include <rendering/renderer.h>

class TestLayer : public Layer {
    public:
        TestLayer();
        virtual ~TestLayer() = default;

        void update() override;

        void start() override;

	private:
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;
		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;
		bgfx::ProgramHandle program;
};
