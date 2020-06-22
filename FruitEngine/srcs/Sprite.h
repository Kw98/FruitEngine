#pragma once

#include <string>

#include <glm/glm.hpp>

namespace FE {

	enum class SpriteMode_e {
		SINGLE,
		MULTIPLE_NORMED,
		MULTIPLE
	};
//
//	struct SpriteSlicer {
//		glm::ivec2	dimensions;
//		glm::vec2	offset;
//		glm::vec2	padding;
//		std::size_t	index;
//	};
//
//#define DEFAULT_SPRITE_SLICER (FE::SpriteSlicer{FE::SpriteMode_e::SINGLE, {0, 0}, {0.0f, 0.0f}, {0.0f, 0.0f}, 1})

	struct Sprite {
		FE::SpriteMode_e	Mode;
		std::string	TextureName;
		glm::ivec2	Dimensions;
		glm::vec2	Offset;
		glm::vec2	Padding;
		std::size_t	Index;
		int	Layer;
	};

}