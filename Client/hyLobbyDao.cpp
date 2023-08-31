#include "hyLobbyDao.h"
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
	LobbyDao::LobbyDao()
	{
	}
	LobbyDao::~LobbyDao()
	{
	}
	void LobbyDao::Initialize()
	{
		
		// 캐릭터 세팅
		Texture* LobbyDao_ = Resources::Load<Texture>(L"LobbyDao"
			, L"..\\Resources\\Image\\Dao\\Idle\\Idle.bmp");

		Animator* at = AddComponent<Animator>();

		at->CreateAnimation(L"LobbyDao", LobbyDao_, Vector2(0.0f, 0.0f), Vector2(52.0f, 55.0f), 1, Vector2(0.0f, 0.0f), 0.6f);
		//at->SetScale(Vector2(1.3f, 1.3f));

		//at->PlayAnimation(L"LobbyDao", true);

	}

	void LobbyDao::Update()
	{
		GameObject::Update();

		Animator* spt = GetComponent<Animator>();

		Vector2 temp = Input::GetMousePosition();

		


	}

	void LobbyDao::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}