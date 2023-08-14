#include "hyVelocitySkate.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hySound.h"



namespace hy
{
	VelocitySkate::VelocitySkate()
	{
		Animator* vst = AddComponent<Animator>();

		Texture* VelocitySkate_ = Resources::Load<Texture>(L"VelocitySkate"
			, L"..\\Resources\\Image\\Items\\skate.bmp");

		vst->CreateAnimation(L"VelocitySkate", VelocitySkate_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		vst->SetScale(Vector2(0.9f, 0.9f));
		vst->PlayAnimation(L"VelocitySkate", true);
	}
	VelocitySkate::~VelocitySkate()
	{
	}
	void VelocitySkate::Initialize()
	{
		Item::Initialize();
		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void VelocitySkate::Update()
	{
		Item::Update();
	}
	void VelocitySkate::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void VelocitySkate::OnCollisionEnter(Collider* other)
	{
		Resources::Find<Sound>(L"EatItem")->Play(false);

	}
	void VelocitySkate::OnCollisionStay(Collider* other)
	{
	}
	void VelocitySkate::OnCollisionExit(Collider* other)
	{
	}
	void VelocitySkate::Idle()
	{
	}
	void VelocitySkate::Use()
	{
	}
	void VelocitySkate::Extinct()
	{
	}
}
