#pragma once
#include "hyScene.h"
#include "hyGameObject.h"
#include "hySceneManager.h"
#include "hyTransform.h"

namespace hy::object
{
	template <typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		//gameObject->Initialize();
		gameObject->SetLayerType(type);
 
		return gameObject;
	}


	template <typename T>
	static __forceinline T* Instantiate(eLayerType type, Vector2 position)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		//gameObject->Initialize();
		gameObject->GetComponent<Transform>()->SetPosition(position);

		return gameObject;
	}

}

