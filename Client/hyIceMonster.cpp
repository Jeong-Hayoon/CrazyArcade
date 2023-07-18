//#include "hyIceMonster.h"
//#include "hyTransform.h"
//#include "hyInput.h"
//#include "hyTime.h"
//#include "hyAnimator.h"
//#include "hyResources.h"
//#include "hyForestMap.h"
//#include "hySpriteRenderer.h"
//#include "hyObject.h"
//#include "hySceneManager.h"
//#include "hyApplication.h"
//#include "hyInput.h"
//#include "hyTexture.h"
//#include "hyResources.h"
//
//// PirateMonster 그대로 사용하고 보스만 아이스 보스로
//namespace hy
//{
//	IceMonster::IceMonster()
//	{
//	}
//	IceMonster::~IceMonster()
//	{
//	}
//	void IceMonster::Initialize()
//	{
//	
//
//		GameObject::Initialize();
//	}
//	void IceMonster::Update()
//	{
//		GameObject::Update();
//
//		Transform* tr = GetComponent<Transform>();
//		Vector2 pos = tr->GetPosition();
//		Animator* anim = GetComponent<Animator>();
//
//		tr->SetPosition(pos);
//		static float MonsterTime = 0.f;
//		MonsterTime += Time::DeltaTime();
//
//		if (MonsterTime < 3)
//		{
//			anim->PlayAnimation(L"ForestMosterRight", true);
//			pos.x += 150.0f * Time::DeltaTime();
//		}
//
//		if (MonsterTime < 6 && MonsterTime > 3)
//		{
//			anim->PlayAnimation(L"ForestMosterDown", true);
//			pos.y += 150.0f * Time::DeltaTime();
//		}
//
//		if (MonsterTime < 9 && MonsterTime > 6)
//		{
//			anim->PlayAnimation(L"ForestMosterLeft", true);
//			pos.x -= 150.0f * Time::DeltaTime();
//		}
//
//		if (MonsterTime < 12 && MonsterTime > 9)
//		{
//			anim->PlayAnimation(L"ForestMosterUp", true);
//			pos.y -= 150.0f * Time::DeltaTime();
//		}
//	}
//	void IceMonster::Render(HDC hdc)
//	{
//		GameObject::Render(hdc);
//	}
//
//}
//
