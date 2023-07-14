#include "hySceneManager.h"
#include "hyTitleScene.h"
#include "hyLobbyScene.h"
#include "hyForestMap.h"
#include "hyIceMap.h"
#include "hyPirateMap.h"



namespace hy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<LobbyScene>(L"LobbyScene");
		CreateScene<ForestMap>(L"ForestMap");
		CreateScene<IceMap>(L"IceMap");
		CreateScene<PirateMap>(L"PirateMap");

		// LoadScene(L"TitleScene");
		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*> ::iterator iter
			= mScenes.find(name);

		
		(iter == mScenes.end())
			return nullptr;
	
		mActiveScene = iter->second;
		return iter->second;

	}

}
