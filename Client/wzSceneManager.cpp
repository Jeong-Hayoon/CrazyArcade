#include "wzSceneManager.h"
#include "wzTitleScene.h"
#include "wzLobbyScene.h"
#include "wzLoginScene.h"
#include "wzPlayScene.h"


namespace wz
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<LoginScene>(L"LoginScene");
		CreateScene<LobbyScene>(L"LobbyScene");
		CreateScene<PlayScene>(L"PlayScene");

		// LoadScene(L"TitleScene");
		LoadScene(L"LoginScene");
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
