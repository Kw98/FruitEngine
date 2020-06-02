#include <iostream>
#include <exception>

#include "Window.h"

namespace FE {

	Window::Window(const glm::ivec2& dimensions, const std::string& name)
		: _dimensions(dimensions)
		, _name(name)
		, _glfWindow(nullptr)
	{
		Window::Init();
	}

	Window::~Window()
	{
		glfwDestroyWindow(_glfWindow);
		glfwTerminate();
	}

	void	Window::Init()
	{
		if (!glfwInit())
			throw std::exception("glfw init error");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		_glfWindow = glfwCreateWindow(_dimensions.x, _dimensions.y, _name.c_str(), NULL, NULL);
		if (!_glfWindow) {
			glfwTerminate();
			throw std::exception("Window creation error");
		}

		glfwMakeContextCurrent(_glfWindow);
		glfwSetWindowTitle(_glfWindow, _name.c_str());
	}

}