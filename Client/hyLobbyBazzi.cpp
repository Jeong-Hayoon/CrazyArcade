#include "hyLobbyBazzi.h"
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
	LobbyBazzi::LobbyBazzi()
	{
	}
	LobbyBazzi::~LobbyBazzi()
	{
	}
	void LobbyBazzi::Initialize()
	{
		// 캐릭터 세팅
		Texture* LobbyBazzi_ = Resources::Load<Texture>(L"LobbyBazzi"
			, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

		Animator* at = AddComponent<Animator>();

		at->CreateAnimation(L"LobbyBazzi", LobbyBazzi_, Vector2(0.0f, 0.0f), Vector2(90.0f, 114.0f), 1, Vector2(0.0f, 0.0f), 0.6f);
		at->SetScale(Vector2(0.7f, 0.7f));
		//at->PlayAnimation(L"LobbyBazzi", true);
	

	}

	void LobbyBazzi::Update()
	{
		GameObject::Update();

		Animator* spt = GetComponent<Animator>();

		Vector2 temp = Input::GetMousePosition();

		// Forest 선택
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 250 && temp.y <= 260 && temp.x >= 360 && temp.x <= 520)
		{
			spt->PlayAnimation(L"ForestPick", true);
			SceneManager::SetActiveMap(1);
		}


	}

	void LobbyBazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}