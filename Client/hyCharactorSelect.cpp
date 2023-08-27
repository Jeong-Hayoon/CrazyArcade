#include "hyCharactorSelect.h"
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
	CharactorSelect::CharactorSelect()
	{
	}
	CharactorSelect::~CharactorSelect()
	{
	}
	void CharactorSelect::Initialize()
	{
		Texture* SelectWindow_ = Resources::Load<Texture>(L"SelectWindow"
			, L"..\\Resources\\Image\\UI\\MapSelect.bmp");

		Animator* spt = AddComponent<Animator>();

		spt->CreateAnimation(L"MapWindow", SelectWindow_, Vector2(0.0f, 0.0f), Vector2(500.0f, 455.0f), 1, Vector2(0.0f, 0.0f), 3.f);

		spt->PlayAnimation(L"MapWindow", true);

	}

	void CharactorSelect::Update()
	{
		GameObject::Update();

		Animator* spt = GetComponent<Animator>();

		Vector2 temp = Input::GetMousePosition();

		// Forest ¼±ÅÃ
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 250 && temp.y <= 260 && temp.x >= 360 && temp.x <= 520)
		{
			spt->PlayAnimation(L"ForestPick", true);
			SceneManager::SetActiveMap(1);
		}


	}

	void CharactorSelect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}