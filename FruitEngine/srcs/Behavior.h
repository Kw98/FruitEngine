#pragma once

#include "GameObject.h"
/*scripting:
-> std::unordered_map<type_index, std::vector<entt>>
on ajoute les scripts via la class scenes
implem destroy qui call la scene pour bien delete
*/
namespace FE {

	class Behavior {
	public:
		Behavior(const std::size_t &id) : _id(id) {}
		virtual ~Behavior() = default;

		FE::GameObject* GameObject() {
			return FE::FRegister->try_get<FE::GameObject>(_id);
		}

		virtual void	Start() {}
		virtual void	FixedUpdate() {}
		virtual void	Update() {}
		virtual void	OnGUI() {}
		virtual void	OnDisable() {}
		virtual void	OnEnable() {}
		virtual void	OnDestroy() {}

		virtual void	OnCollisionEnter() {}
		virtual void	OnCollisionExit() {}
		virtual void	OnCollisionStay()	{}
		virtual void	OnTriggerEnter() {}
		virtual void	OnTriggerExit() {}
		virtual void	OnTriggerStay() {}

		virtual void	OnDrawGizmos()	{}

	private:
		std::size_t	_id;
	};
}