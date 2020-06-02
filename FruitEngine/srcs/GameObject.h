#pragma once

#include "FRegister.h"
#include "SceneManager.h"

namespace FE {

	struct GameObject {
		template<typename T>
		T* GetComponent() {
			return FE::FRegister->try_get<T>(Id);
		}

		template<typename T>
		T* GetBehavior() {
			return FE::FRegister->get<T*>(Id);
		}

		template<typename T>
		void	AddBehavior(T& behavior) {
			FE::SceneManager::Instance()->Scenes()[SceneId].AddBehavior(Id, behavior);
		}

		template<typename T, typename ...Args>
		void	AddBehavior(Args&& ...args) {
			FE::SceneManager::Instance()->Scenes()[SceneId].AddBehavior<T>(Id, args...);
		}

		std::size_t	Id;
		std::size_t	SceneId;
		std::string	Name;
		std::string	Tag;
		bool	enable;
	};

}