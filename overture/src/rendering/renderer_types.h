#pragma once

#include <defines.h>

#include <bgfx/bgfx.h>

namespace renderer {
	struct PosColorVertex {
		f32 x;
		f32 y;
		f32 z;
		uint32_t abgr;
	};

	struct Model {
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;

		bgfx::ProgramHandle program;
	};
}
