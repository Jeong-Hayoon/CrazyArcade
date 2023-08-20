#include "hySceneManager.h"
#include "hyTitleScene.h"
#include "hyLobbyScene.h"
#include "hyToolScene.h"
#include "hyLogoScene.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyForestMap1.h"
#include "hyForestMap2.h"
#include "hyForestMap3.h"

#include "hyIceMap1.h"
#include "hyIceMap2.h"
#include "hyIceMap3.h"

#include "hyPirateMap1.h"
#include "hyPirateMap2.h"
#include "hyPirateMap3.h"

#include "hyBazzi.h"





namespace hy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Bazzi* SceneManager::mBazzi;

	void SceneManager::Initialize()
	{
		CreateScene<LogoScene>(L"LogoScene");
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<LobbyScene>(L"LobbyScene");

		CreateScene<ForestMap1>(L"ForestMap1");
		CreateScene<ForestMap2>(L"ForestMap2");
		CreateScene<ForestMap3>(L"ForestMap3");

		CreateScene<IceMap1>(L"IceMap1");
		CreateScene<IceMap2>(L"IceMap2");
		CreateScene<IceMap3>(L"IceMap3");

		CreateScene<PirateMap1>(L"PirateMap1");
		CreateScene<PirateMap2>(L"PirateMap2");
		CreateScene<PirateMap3>(L"PirateMap3");

		CreateScene<ToolScene>(L"ToolScene");


		LoadScene(L"ForestMap3");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}


	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		mActiveScene->Exit();


		std::map<std::wstring, Scene*> ::iterator iter
			= mScenes.find(name);

		
		if(iter == mScenes.end())
			return nullptr;
	
		mActiveScene = iter->second;
		mActiveScene->Enter();
		return iter->second;

	}

}
