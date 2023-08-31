#include "hyLobbyCharactor.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"
#include "hyResources.h"
#include "hyAnimation.h"
#include "hyAnimator.h"
#include "hySceneManager.h"

namespace hy
{
	LobbyCharactor::LobbyCharactor()
	{
	}
	LobbyCharactor::~LobbyCharactor()
	{
	}
	void LobbyCharactor::Initialize()
	{
		// 캐릭터 세팅
		Texture* LobbyBazzi_ = Resources::Load<Texture>(L"LobbyBazzi"
			, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

		Texture* LobbyDao_ = Resources::Load<Texture>(L"LobbyDao"
			, L"..\\Resources\\Image\\Dao\\Idle\\Idle.bmp");

		Animator* at = AddComponent<Animator>();

		at->CreateAnimation(L"LobbyBazzi", LobbyBazzi_, Vector2(0.0f, 0.0f), Vector2(90.0f, 114.0f), 1, Vector2(0.0f, 0.0f), 0.6f);
		at->CreateAnimation(L"LobbyDao", LobbyDao_, Vector2(0.0f, 0.0f), Vector2(52.0f, 55.0f), 1, Vector2(0.0f, 0.0f), 0.6f);

		at->SetScale(Vector2(0.7f, 0.7f));
		//at->PlayAnimation(L"LobbyBazzi", true);
	

	}

	void LobbyCharactor::Update()
	{
		GameObject::Update();

	}

	void LobbyCharactor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}