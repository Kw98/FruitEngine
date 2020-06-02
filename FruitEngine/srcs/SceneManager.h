#pragma once

#include <unordered_map>
#include <utility>
#include <memory>

#include "IdManager.hpp"
#include "Scene.h"

namespace FE {

	class SceneManager {
	public:
		static FE::SceneManager* Instance() {
			static std::unique_ptr<FE::SceneManager>	sceneManager(new FE::SceneManager());
			return sceneManager.get();
		}
		
		~SceneManager() {}

		FE::Scene& CreateScene(const std::string& sceneName);

		void	ChangeScene(const std::size_t& sceneId);
		void	ChangeScene(const std::string& sceneName);

		FE::Scene&	Current() { return _scenes[_current]; }
		std::unordered_map<std::size_t, Scene>& Scenes() { return _scenes; }

	private:
		SceneManager() : _idManager(10), _current(0) {}

		g_reg::IdManager	_idManager;
		std::size_t	_current;
		std::unordered_map<std::size_t, FE::Scene>	_scenes;
	};
}