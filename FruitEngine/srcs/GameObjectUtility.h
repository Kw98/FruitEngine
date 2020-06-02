#pragma once

#include "SceneManager.h"
#include "Transform.h"
#include "FRegister.h"

class GOutility {
public:
	static FE::GameObject* FindGameObjectWithName(const std::string& name, FE::Scene& scene = FE::SceneManager::Instance()->Current()) {
		for (auto&& id : scene.Entities()) {
			FE::GameObject* go = FE::FRegister->try_get<FE::GameObject>(id);
			if (go->Name == name)
				return go;
		}
		return nullptr;
	}

	static FE::GameObject* FindGameObjectWithTag(const std::string& tag, FE::Scene& scene = FE::SceneManager::Instance()->Current()) {
		for (auto&& id : scene.Entities()) {
			FE::GameObject* go = FE::FRegister->try_get<FE::GameObject>(id);
			if (go->Tag == tag)
				return go;
		}
		return nullptr;
	}

	static FE::GameObject* FindGameObjectWithId(const std::size_t& id, FE::Scene& scene = FE::SceneManager::Instance()->Current()) {
		for (auto&& entt : scene.Entities()) {
			if (entt == id)
				return FE::FRegister->try_get<FE::GameObject>(id);
		}
		return nullptr;
	}

	static std::vector<FE::GameObject*>	FindGameObjectsWithTag(const std::string& tag, FE::Scene& scene = FE::SceneManager::Instance()->Current()) {
		std::vector<FE::GameObject*>	vec;
		for (auto&& entt : scene.Entities()) {
			FE::GameObject* go = FE::FRegister->try_get<FE::GameObject>(entt);
			if (go->Tag == tag)
				vec.push_back(go);
		}
		return vec;
	}

	static std::vector<FE::GameObject*>	FindGameObjectsWithName(const std::string& name, FE::Scene& scene = FE::SceneManager::Instance()->Current()) {
		std::vector<FE::GameObject*>	vec;
		for (auto&& entt : scene.Entities()) {
			FE::GameObject* go = FE::FRegister->try_get<FE::GameObject>(entt);
			if (go->Name == name)
				vec.push_back(go);
		}
		return vec;
	}
};