#pragma once

#include <iostream>

#include <memory>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace FE {

	constexpr int	FE_KEY_NONE = 0;
	constexpr int	FE_KEY_DOWN = GLFW_PRESS;
	constexpr int	FE_KEY_UP = GLFW_RELEASE;

	class Mouse {
	public:
		Mouse() : _entered(true), _pos({ 0, 0 }) {}
		~Mouse() {}

		glm::vec2& Pos() { return _pos; }
		bool&	Entered() { return _entered; }
		std::unordered_map<int, int>& Buttons() { return _buttons; }

	private:
		bool	_entered;
		glm::vec2	_pos;
		std::unordered_map<int, int>	_buttons;
	};

	class Input {
	public:
		static Input* Instance() {
			static std::unique_ptr<Input>	input(new Input());
			return input.get();
		}

		~Input() {}

		void	update(GLFWwindow *window) {
			for (int i = 0; i < GLFW_KEY_LAST; i++) {
				if (glfwGetKey(window, i) == FE_KEY_DOWN)
					_keys.emplace(i, FE_KEY_DOWN);
			}
			for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
				if (glfwGetMouseButton(window, i) == FE_KEY_DOWN)
					_mouse.Buttons().emplace(i, FE_KEY_DOWN);
			}
		}

		static FE::Mouse& Mouse() { return FE::Input::Instance()->_mouse; }
		static std::unordered_map<int, int>& Keys() { return FE::Input::Instance()->_keys; }
		static bool	getkey(int key, int status = FE_KEY_DOWN) {
			FE::Input* input = FE::Input::Instance();
			return input->_keys.find(key) != input->_keys.end() && input->_keys[key] == status; 
		}
		static bool	getMouseButton(int button, int status = FE_KEY_DOWN) {
			FE::Input* input = FE::Input::Instance();
			return input->_mouse.Buttons().find(button) != input->_mouse.Buttons().end() && input->_mouse.Buttons()[button] == status;
		}
		static glm::vec2& getMousePos() { return FE::Input::Mouse().Pos(); }
		static double& VerticalScroll() { return FE::Input::Instance()->_verticalScroll; }
		static double& HorizontalScroll() { return FE::Input::Instance()->_horizontalScroll; }

	private:
		Input() {}

		std::unordered_map<int, int>	_keys;
		FE::Mouse	_mouse;
		double	_verticalScroll;
		double	_horizontalScroll;
	};

	class InputReceiver {
	public:

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == FE_KEY_UP)
				FE::Input::Keys().emplace(key, action);
		}

		static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
			FE::Input::Mouse().Pos() = { xpos, ypos };
		}

		static void cursor_enter_callback(GLFWwindow* window, int entered) {
			FE::Input::Mouse().Entered() = entered == 1;
		}

		static void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			if (action == FE_KEY_UP)
				FE::Input::Mouse().Buttons().emplace(button, action);
		}

		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
			FE::Input::HorizontalScroll() = xoffset;
			FE::Input::VerticalScroll() = yoffset;
		}

	};

}
