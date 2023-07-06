#pragma once
#include "wzScene.h"

namespace wz
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		template<typename T>

		static T* CreatScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mScene.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }


	private:
		static std::map <std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
	};
}

