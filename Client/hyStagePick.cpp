#include "hyStagePick.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"
#include "hyResources.h"
#include "hyAnimation.h"
#include "hyAnimator.h"

namespace hy
{
	StagePick::StagePick()
	{
	}
	StagePick::~StagePick()
	{
	}
	void StagePick::Initialize()
	{
		Texture* SelectWindow_ = Resources::Load<Texture>(L"SelectWindow"
			, L"..\\Resources\\Image\\UI\\MapSelect.bmp");

		Texture* SelectForest_ = Resources::Load<Texture>(L"SelectForest"
			, L"..\\Resources\\Image\\UI\\MapSelect_Forest.bmp");
		Texture* SelectIce_= Resources::Load<Texture>(L"SelectIce"
			, L"..\\Resources\\Image\\UI\\MapSelect_Ice.bmp");
		Texture* SelectPirate_= Resources::Load<Texture>(L"SelectPirate"
			, L"..\\Resources\\Image\\UI\\MapSelect_Pirate.bmp");

		Animator* spt = AddComponent<Animator>();

		spt->CreateAnimation(L"MapWindow", SelectWindow_, Vector2(0.0f, 0.0f), Vector2(700.0f, 637.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		spt->CreateAnimation(L"ForestPick", SelectForest_, Vector2(0.0f, 0.0f), Vector2(700.0f, 637.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		spt->CreateAnimation(L"IcePick", SelectIce_, Vector2(0.0f, 0.0f), Vector2(700.0f, 637.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		spt->CreateAnimation(L"PiratePick", SelectPirate_, Vector2(0.0f, 0.0f), Vector2(700.0f, 637.0f), 1, Vector2(0.0f, 0.0f), 3.f);

		spt->PlayAnimation(L"MapWindow", true);

	}

	void StagePick::Update()
	{
		GameObject::Update();

		Animator* spt = AddComponent<Animator>();

		Vector2 temp = Input::GetMousePosition();

		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 250 && temp.y <= 265 && temp.x >= 300 && temp.x <= 470)
		{
			spt->PlayAnimation(L"ForestPick", true);
			// LoadScene -> ForestMap할 flag 변수 생성

		}
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 270 && temp.y <= 285 && temp.x >= 300 && temp.x <= 470)
		{
			spt->PlayAnimation(L"IcePick", true);
			// LoadScene -> IceMap할 flag 변수 생성
		}
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 340 && temp.y <= 355 && temp.x >= 300 && temp.x <= 470)
		{
			spt->PlayAnimation(L"PiratePick", true);
			// LoadScene -> PirateMap할 flag 변수 생성
		}
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 580 && temp.y <= 615 && temp.x >= 205 && temp.x <= 340)
		{
			Destroy(this);
		}

	}

	void StagePick::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}