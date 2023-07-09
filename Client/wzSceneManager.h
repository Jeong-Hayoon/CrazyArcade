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

		static T* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		static std::map <std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		// 트리 자료구조
		// key value 구조로 이루어져 있따.
		// key는 데이터를 검색하는 용도
		// value 실제 우리가 써야할 데이터	
	};
}

