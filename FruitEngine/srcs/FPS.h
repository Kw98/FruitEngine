#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

class FPS
{
public:
	FPS() {
		_lastTime = glfwGetTime();
		_frames = 0;
	}

	~FPS() = default;

	void	update() {
		double current = glfwGetTime();
		_frames++;
		if (current - _lastTime >= 1.0) {
			std::cout << 1000.0 / static_cast<double>(_frames) << "ms/frame" << std::endl;
			std::cout << _frames << "fps" << std::endl;
			_lastTime = current;
			_frames = 0;
		}
	}

private:
	double	_lastTime;
	int	_frames;

};
