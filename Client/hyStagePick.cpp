#include "hyStagePick.h"
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

		spt->CreateAnimation(L"MapWindow", SelectWindow_, Vector2(0.0f, 0.0f), Vector2(500.0f, 455.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		spt->CreateAnimation(L"ForestPick", SelectForest_, Vector2(0.0f, 0.0f), Vector2(500.0f, 455.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		spt->CreateAnimation(L"IcePick", SelectIce_, Vector2(0.0f, 0.0f), Vector2(500.0f, 455.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		spt->CreateAnimation(L"PiratePick", SelectPirate_, Vector2(0.0f, 0.0f), Vector2(500.0f, 455.0f), 1, Vector2(0.0f, 0.0f), 3.f);

		spt->PlayAnimation(L"MapWindow", true);

	}

	void StagePick::Update()
	{
		GameObject::Update();

		Animator* spt = GetComponent<Animator>();

		Vector2 temp = Input::GetMousePosition();

		// Forest ����
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 250 && temp.y <= 260 && temp.x >= 360 && temp.x <= 520)
		{
			spt->PlayAnimation(L"ForestPick", true);
			SceneManager::SetActiveMap(1);
		}

		// Ice ����
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 260 && temp.y <= 270 && temp.x >= 360 && temp.x <= 520)
		{
			spt->PlayAnimation(L"IcePick", true);
			SceneManager::SetActiveMap(2);

		}

		// Pirate ����
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 310 && temp.y <= 320 && temp.x >= 360 && temp.x <= 520)
		{
			spt->PlayAnimation(L"PiratePick", true);
			SceneManager::SetActiveMap(3);
		}

	}

	void StagePick::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}