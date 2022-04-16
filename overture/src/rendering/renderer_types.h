#pragma once

#include <defines.h>

#include <bgfx/bgfx.h>
#include <unordered_map>

namespace renderer {
	struct PosColorVertex {
		f32 x;
		f32 y;
		f32 z;
		uint32_t abgr;

		bool operator==(const PosColorVertex& other) const {
			return x == other.x && y == other.y && z == other.z && abgr == other.abgr;
		}
	};

	struct Model {
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;

		bgfx::ProgramHandle program;
	};
}
