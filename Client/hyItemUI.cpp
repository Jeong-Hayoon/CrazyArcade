#include "hyItemUI.h"
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
	ItemUI::ItemUI()
	{
	}
	ItemUI::~ItemUI()
	{
	}
	void ItemUI::Initialize()
	{
		// 캐릭터 세팅
		Texture* NeedleUI_ = Resources::Load<Texture>(L"needleui"
			, L"..\\Resources\\Image\\UI\\needleUI.bmp");

		Texture* ShieldUI_ = Resources::Load<Texture>(L"shieldui"
			, L"..\\Resources\\Image\\UI\\shieldUI.bmp");

		Texture* NoneUI_ = Resources::Load<Texture>(L"noneui"
			, L"..\\Resources\\Image\\UI\\Item_None.bmp");

		Animator* at = AddComponent<Animator>();

		at->CreateAnimation(L"NeedleUI", NeedleUI_, Vector2(0.0f, 0.0f), Vector2(38.0f, 38.0f), 1, Vector2(0.0f, 0.0f), 0.6f);
		at->CreateAnimation(L"ShieldUI", ShieldUI_, Vector2(0.0f, 0.0f), Vector2(38.0f, 38.0f), 1, Vector2(0.0f, 0.0f), 0.6f);
		at->CreateAnimation(L"NoneUI", NoneUI_, Vector2(0.0f, 0.0f), Vector2(38.0f, 38.0f), 1, Vector2(0.0f, 0.0f), 0.6f);

		//at->PlayAnimation(L"LobbyBazzi", true);

	}

	void ItemUI::Update()
	{
		GameObject::Update();

	}

	void ItemUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}