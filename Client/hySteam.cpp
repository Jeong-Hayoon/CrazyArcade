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
		Destroy(this);
	}

}

