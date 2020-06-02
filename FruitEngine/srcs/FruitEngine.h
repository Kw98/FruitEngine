#pragma once

#include <glm/vec2.hpp>
#include "FRegister.h"
#include "Window.h"
#include "SceneManager.h"

constexpr std::size_t DEFAULT_MAX_ENTITY = 100;
constexpr std::size_t DEFAULT_MAX_COMPONENT = 10;

namespace FE {

	class FruitEngine {
	public:
		FruitEngine(const glm::ivec2 &windowDimensions, const std::string &name);
		~FruitEngine();

		//FE::Scene	&NewScene(const std::string &name);
		void	Run();

		FE::Window& Window() { return _window; }

	private:
		FE::Window	_window;
	};
}