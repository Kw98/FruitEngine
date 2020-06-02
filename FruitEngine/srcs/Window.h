#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace FE {

	class Window {
	public:
		Window(const glm::ivec2 &dimensions, const std::string &name);
		~Window();

		GLFWwindow*	GLFWindow() { return _glfWindow; }
		glm::ivec2&	Dimensions() { return _dimensions; }
		std::string&	Name() { return _name; }

	private:
		void	Init();
		
		glm::ivec2	_dimensions;
		std::string	_name;
		GLFWwindow* _glfWindow;
	};

}