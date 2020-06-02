#pragma once

#include <glm/glm.hpp>

namespace FE {
	struct Transform {
		glm::vec3	position;
		glm::vec3	rotation;
		glm::vec3	scale;
		std::size_t	parent;
	};
}