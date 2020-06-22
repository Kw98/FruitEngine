#include "Scene.h"
#include "Transform.h"
#include "Behavior.h"
#include "GameObject.h"

namespace FE {

	void	Scene::Load()
	{
		_loader(*this);
		// plutot call une callback user qui créer la scène avec tout les objets et call le start ?
		for (auto&& behavior : _scripts) {
			for (auto&& entt : behavior.second) {
				if (FE::FRegister->get<GameObject>(entt).enable == true)
					static_cast<g_reg::sparse_set<FE::Behavior*>*>(FE::FRegister->get_native_pool_by_type_index(behavior.first))->get(entt)->Start();
			}
		}
	}

	void	Scene::UnLoad()
	{
		_deletedEntities.clear();
		_scripts.clear();
		for (auto&& entt : _entities)
			FE::FRegister->delete_entity(entt);
	}

	// avoir juste une list des scripts par scene et passer directement via le sparset et call les scripts
	// avoir un set d'objet disable et find si l'objet est dedans on lance
	//
	//
	void	Scene::Update()
	{
		//when working on physics change this part ith fixedUpdate
		//for (auto&& behavior : _scripts) {
		//	for (auto&& entt : behavior.second) {
		//		if (FE::FRegister->get<GameObject>(entt).enable == true)
		//			static_cast<g_reg::sparse_set<FE::Behavior*>*>(FE::FRegister->get_native_pool_by_type_index(behavior.first))->get(entt)->FixedUpdate();
		//	}
		//}
		//
		for (auto&& behavior : _scripts) {
			for (auto&& entt : behavior.second) {
				if (FE::FRegister->get<GameObject>(entt).enable == true)
					static_cast<g_reg::sparse_set<FE::Behavior*>*>(FE::FRegister->get_native_pool_by_type_index(behavior.first))->get(entt)->Update();
			}
		}

		CleanDeletedEntities();
	}

	void	Scene::Render()
	{
		// no render system done
	}


	FE::GameObject* Scene::EmptyGameObject()
	{
		std::size_t id = FE::FRegister->create();
		_entities.push_back(id);
		FE::FRegister->construct<GameObject>(id, id, _id, "GameObject", "none", true);
		FE::FRegister->construct<Transform>(id, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, std::size_t{ 0 });
		return FE::FRegister->try_get<GameObject>(id);
	}

	void	Scene::CleanDeletedEntities() {
		for (auto&& id : _deletedEntities)
			FE::FRegister->delete_entity(id);
		_deletedEntities.clear();
	}

}