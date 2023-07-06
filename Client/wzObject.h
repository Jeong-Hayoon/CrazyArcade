#pragma once
#include "wzScene.h"
#include "wzGameObject.h"
#include "wzSceneManager.h"

namespace wz::object
{
	template <typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		 
		return gameObject;
	}

}

