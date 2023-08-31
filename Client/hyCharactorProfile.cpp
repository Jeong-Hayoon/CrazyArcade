#include "hyCharactorProfile.h"
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
	CharactorProfile::CharactorProfile()
	{
	}
	CharactorProfile::~CharactorProfile()
	{
	}
	void CharactorProfile::Initialize()
	{
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		Texture* DAProfile = Resources::Load<Texture>(L"DAProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameDao.bmp");

		Animator* at = AddComponent<Animator>();

		at->CreateAnimation(L"BazziProfile", BZProfile, Vector2(0.0f, 0.0f), Vector2(92.0f, 73.0f), 1, Vector2(0.0f, 0.0f), 0.6f);
		at->CreateAnimation(L"DaoProfile", DAProfile, Vector2(0.0f, 0.0f), Vector2(92.0f, 72.0f), 1, Vector2(0.0f, 0.0f), 0.6f);

		at->SetScale(Vector2(0.6f, 0.6f));
		//at->PlayAnimation(L"LobbyBazzi", true);


	}

	void CharactorProfile::Update()
	{
		GameObject::Update();

	}

	void CharactorProfile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}