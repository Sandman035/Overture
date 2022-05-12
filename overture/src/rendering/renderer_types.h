#pragma once

#include <defines.h>

#include <cstdint>

namespace renderer {
	struct PosColorVertex {
		f32 x;
		f32 y;
		f32 z;
		uint32_t abgr;
	};
}
