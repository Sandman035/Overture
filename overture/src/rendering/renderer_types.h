#pragma once

#include <defines.h>

#include <glm/glm.hpp>

namespace renderer {
	struct PosTexColor {
		glm::vec3 pos;
		glm::vec2 tex;
		glm::vec3 color;
	};
}
