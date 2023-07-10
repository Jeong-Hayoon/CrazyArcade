#include "hySceneManager.h"
#include "hyTitleScene.h"
#include "hyLobbyScene.h"
#include "hyLoginScene.h"
#include "hyPlayScene.h"


namespace hy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<LobbyScene>(L"LobbyScene");
		CreateScene<PlayScene>(L"PlayScene");

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

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		return iter->second;

	}

}
