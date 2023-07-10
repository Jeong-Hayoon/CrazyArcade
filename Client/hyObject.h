#pragma once
#include "hyScene.h"
#include "hyGameObject.h"
#include "hySceneManager.h"

namespace hy::object
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

