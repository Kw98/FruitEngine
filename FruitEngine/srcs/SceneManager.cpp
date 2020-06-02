#include <algorithm>
#include "SceneManager.h"

namespace FE {

	FE::Scene& SceneManager::CreateScene(const std::string& sceneName)
	{
		std::size_t	id = _idManager.use();
		_scenes.emplace(id, Scene(sceneName, id));
		if (_scenes.size() == 1)
			_current = id;
		return _scenes[id];
	}

	void	SceneManager::ChangeScene(const std::size_t& sceneId)
	{
		auto elem = std::find_if(_scenes.begin(), _scenes.end(), [&sceneId](const std::pair<std::size_t, FE::Scene>& s1) { return s1.first == sceneId; });
		if (elem == _scenes.end())
			return;
		if (_scenes.size() > 1)
			_scenes[_current].UnLoad();
		_current = sceneId;
		_scenes[_current].Load();
	}

	void	SceneManager::ChangeScene(const std::string& sceneName) 
	{
		auto elem = std::find_if(_scenes.begin(), _scenes.end(), [&sceneName](const std::pair<std::size_t, FE::Scene>& s1) { return s1.second.Name() == sceneName; });
		if (elem == _scenes.end())
			return;
		if (_scenes.size() > 1)
			_scenes[_current].UnLoad();
		_current = elem->first;
		_scenes[_current].Load();
	}
}