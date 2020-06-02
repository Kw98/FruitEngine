#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "Input.h"
#include "FruitEngine.h"
#include "FPS.h"
#include "Transform.h"


namespace FE {

	FruitEngine::FruitEngine(const glm::ivec2& windowDimensions, const std::string& name)
		: _window(windowDimensions, name)
	{
		if (FE::FRegister != nullptr) {
			delete FE::FRegister;
			FE::FRegister = nullptr;
		}
		FE::FRegister = new g_reg::GRegister(DEFAULT_MAX_ENTITY, DEFAULT_MAX_COMPONENT);
		std::size_t reservedId = FE::FRegister->create();
		FE::FRegister->construct<Transform>(reservedId, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, std::size_t{ 0 });
		glfwSetKeyCallback(_window.GLFWindow(), FE::InputReceiver::key_callback);
		glfwSetCursorPosCallback(_window.GLFWindow(), FE::InputReceiver::cursor_pos_callback);
		glfwSetCursorEnterCallback(_window.GLFWindow(), FE::InputReceiver::cursor_enter_callback);
		glfwSetMouseButtonCallback(_window.GLFWindow(), FE::InputReceiver::mouse_button_callback);
		glfwSetScrollCallback(_window.GLFWindow(), FE::InputReceiver::scroll_callback);
	}

	FruitEngine::~FruitEngine()
	{
		delete FE::FRegister;
		FE::FRegister = nullptr;
	}

	//FE::Scene& FruitEngine::NewScene(const std::string& name)
	//{

	//}

	void	FruitEngine::Run()
	{
		FPS fps;
		//if (FE::SceneManager::Instance()->Scenes().size() < 1)
		//	return;
		//FE::SceneManager::Instance()->Current().Load();
		while (!glfwWindowShouldClose(_window.GLFWindow())) {
			glClearColor(.0f, .0f, .0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST); // enable feature

			// do whatever
			FE::Input::Instance()->update(_window.GLFWindow());

			FE::SceneManager::Instance()->Current().Update();
			FE::SceneManager::Instance()->Current().Render();

			for (auto&& key : FE::Input::Keys()) {
				if (key.second == FE::FE_KEY_DOWN)
					std::cout << "keycode: " << key.first << " is pressed" << std::endl;
				else if (key.second == FE::FE_KEY_UP)
					std::cout << "keycode: " << key.first << " is released" << std::endl;
			}

			//if (FE::Input::Mouse().Entered() == true)
			//	std::cout << "mouse entered window" << std::endl;
			//else
			//	std::cout << "mouse went out of window" << std::endl;

			for (auto&& mouseb : FE::Input::Mouse().Buttons()) {
				if (mouseb.second == FE::FE_KEY_DOWN)
					std::cout << "mouse b code: " << mouseb.first << " is pressed" << std::endl;
				else if (mouseb.second == FE::FE_KEY_UP)
					std::cout << "mouse b code: " << mouseb.first << " is released" << std::endl;
			}

			/*std::cout << "mouse pos: " << glm::to_string(FE::Input::Mouse().Pos()) << std::endl;*/

			FE::Input::Keys().clear();
			FE::Input::Mouse().Buttons().clear();

			/* Swap front and back buffers */
			glfwSwapBuffers(_window.GLFWindow());
			/* Poll for and process events */
			glfwPollEvents();
			fps.update(); // fps printer
		}
	}

}