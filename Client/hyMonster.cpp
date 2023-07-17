#include "hyMonster.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyForestMap.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"

namespace hy
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMosterUp", L"..\\Resources\\Image\\Monster\\Forest\\Up");
		mt->CreateAnimationFolder(L"ForestMosterDown", L"..\\Resources\\Image\\Monster\\Forest\\Down");
		mt->CreateAnimationFolder(L"ForestMosterRight", L"..\\Resources\\Image\\Monster\\Forest\\Right");
		mt->CreateAnimationFolder(L"ForestMosterLeft", L"..\\Resources\\Image\\Monster\\Forest\\Left");
		mt->CreateAnimationFolder(L"ForestMonsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die"); 
		mt->PlayAnimation(L"ForestMosterRight", true);

		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();
		tr->SetPosition(pos);
	}
	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

