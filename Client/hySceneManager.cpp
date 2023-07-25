#include "hySceneManager.h"
#include "hyTitleScene.h"
#include "hyLobbyScene.h"
#include "hyForestMap1.h"
#include "hyIceMap1.h"
#include "hyPirateMap.h"
#include "hyToolScene.h"

namespace hy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<LobbyScene>(L"LobbyScene");
		CreateScene<ForestMap1>(L"ForestMap");
		CreateScene<IceMap1>(L"IceMap");
		CreateScene<PirateMap>(L"PirateMap");
		CreateScene<ToolScene>(L"ToolScene");


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

		
		if(iter == mScenes.end())
			return nullptr;
	
		mActiveScene = iter->second;
		return iter->second;

	}

}
