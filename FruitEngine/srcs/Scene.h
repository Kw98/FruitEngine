#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

#include "FRegister.h"

namespace FE {

	struct GameObject;

	class Scene {
	public:
		using LoadingFunction = std::function<void(FE::Scene&)>;

		Scene(const std::string& name, const std::size_t& id, const FE::Scene::LoadingFunction& loadfunction) : _name(name), _id(id), _loader(loadfunction) {}
		Scene() : _name("none"), _id(0), _loader([](FE::Scene& sc) { std::cout << "none" << std::endl; }) {}
		~Scene() {
			for (auto&& entt : _entities)
				FE::FRegister->delete_entity(entt);
		}

		void	Load();
		void	UnLoad();
		void	Update();
		void	Render();

		const std::string&	Name() const { return _name; }
		const std::size_t& Id() const { return _id; }
		std::vector<std::size_t>	&Entities() { return _entities; }

		FE::GameObject* EmptyGameObject();

		template<typename T>
		void	AddBehavior(const std::size_t& id, T& behavior) {
			std::type_index ctype = std::type_index(typeid(T));
			if (std::find(_scripts[ctype].begin(), _scripts[ctype].end(), ctype) == _scripts[ctype].end()) {
				_scripts[ctype].push_back(id);
				FE::FRegister->assign(id, behavior);
			}
		}

		template<typename T, typename ...Args>
		void	AddBehavior(const std::size_t& id, Args&& ...args) {
			std::type_index ctype = std::type_index(typeid(T));
			if (std::find(_scripts[ctype].begin(), _scripts[ctype].end(), ctype) == _scripts[ctype].end()) {
				_scripts[ctype].push_back(id);
				FE::FRegister->construct<T>(id, args...);
			}
		}

		void	DestroyGameObject(const std::size_t& id) {
			if (std::find(_deletedEntities.begin(), _deletedEntities.end(), id) == _deletedEntities.end())
				_deletedEntities.push_back(id);
		}


	private:

		void	CleanDeletedEntities();


		std::string	_name;
		std::size_t	_id;
		FE::Scene::LoadingFunction	_loader;
		std::vector<std::size_t>	_entities;
		std::vector<std::size_t>	_deletedEntities;
		std::unordered_map<std::type_index, std::vector<std::size_t>>	_scripts;
	};
}