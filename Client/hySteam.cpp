#include "hySteam.h"
#include "hyTransform.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
// #include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBazzi.h"
#include "hyCollider.h"
#include "hyBalloon.h"
#include "hyDevil.h"
#include "hyNeedle.h"
#include "hyPotionMax.h"
#include "hyPotion.h"
#include "hyVelocitySkate.h"


// �ڽ��� �Ҹ�ɶ� ȿ��
// ���� Ȯ���� �Ҹ�� �Ŀ��� �������� �� ��ġ�� ������(��ü ����)

namespace hy
{
	Steam::Steam()
		: mState(eState::Make)
	{
		Animator* st = AddComponent<Animator>();
		st->CreateAnimationFolder(L"Steam", L"..\\Resources\\Image\\Effect\\Crashed", Vector2(0.f, 0.f), 0.1f);
		st->SetScale(Vector2(1.f, 1.f));

		st->PlayAnimation(L"Steam", false);
	}
	Steam::~Steam()
	{
	}
	void Steam::Initialize()
	{
	}
	void Steam::Update()
	{
		GameObject::Update();

		// tab + enter �ϸ� ����ġ ����
		switch (mState)
		{
		case hy::Steam::eState::Make:
			Make();
			break;
		case hy::Steam::eState::Extinct:
			Extinct();
			break;
		case hy::Steam::eState::End:
			break;
		default:
			break;
		}

	}
	void Steam::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Steam::Make()
	{
		Animator* st = GetComponent<Animator>();

		if (st->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}

	}

	void Steam::Extinct()
	{
		Transform* tr = GetComponent<Transform>();

		int ItemSelect = rand() % 6;

		if (ItemSelect == 0)
		{
			// Balloon ������ setting
			Balloon* Balloon_1 = object::Instantiate<Balloon>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// Balloon ������ �浹 ����
			Collider* Ballooncol = Balloon_1->AddComponent<Collider>();
			// Balloon ������ �浹 �簢�� ������ ����
			Ballooncol->SetSize(Vector2(10.0f, 30.0f));
		}
		else if (ItemSelect == 1)
		{
			// Devil ������ setting
			Devil* Devil_1 = object::Instantiate<Devil>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));
	
			// Devil ������ �浹 ����
			Collider* Devilcol = Devil_1->AddComponent<Collider>();
			// Devil ������ �浹 �簢�� ������ ����
			Devilcol->SetSize(Vector2(10.0f, 30.0f));
			Devilcol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 2)
		{
			// Potion ������ setting
			Potion* Potion_1 = object::Instantiate<Potion>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// Potion ������ �浹 ����
			Collider* Potioncol = Potion_1->AddComponent<Collider>();
			// Potion ������ �浹 �簢�� ������ ����
			Potioncol->SetSize(Vector2(10.0f, 30.0f));
			Potioncol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 3)
		{
			// Needle ������ setting
			Needle* Needle_1 = object::Instantiate<Needle>(eLayerType::UseItem, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// Needle ������ �浹 ����
			Collider* Needlecol = Needle_1->AddComponent<Collider>();
			// Needle ������ �浹 �簢�� ������ ����
			Needlecol->SetSize(Vector2(10.0f, 30.0f));
			Needlecol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 4)
		{
			// PotionMax ������ setting
			PotionMax* PotionMax_1 = object::Instantiate<PotionMax>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// PotionMax ������ �浹 ����
			Collider* PotionMaxcol = PotionMax_1->AddComponent<Collider>();
			// PotionMax ������ �浹 �簢�� ������ ����
			PotionMaxcol->SetSize(Vector2(10.0f, 30.0f));
			PotionMaxcol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 5)
		{
			// VelocitySkate ������ setting
			VelocitySkate* VelocitySkate_1 = object::Instantiate<VelocitySkate>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// VelocitySkate ������ �浹 ����
			Collider* VelocitySkatecol = VelocitySkate_1->AddComponent<Collider>();
			// VelocitySkate ������ �浹 �簢�� ������ ����
			VelocitySkatecol->SetSize(Vector2(10.0f, 30.0f));
			VelocitySkatecol->SetOffset(Vector2(0.0f, 0.0f));
		}

		Destroy(this);
	}

}

//Balloon,
//Devil,
//Needle,
//Potion,
//PotionMax,
//VelocitySkate,