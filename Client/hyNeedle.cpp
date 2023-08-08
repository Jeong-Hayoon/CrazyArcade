#include "hyNeedle.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"

// ¹Ù´Ã
namespace hy
{
	Needle::Needle()
	{
		Animator* nt = AddComponent<Animator>();

		Texture* Needle_ = Resources::Load<Texture>(L"Needle"
			, L"..\\Resources\\Image\\Items\\needle.bmp");

		nt->CreateAnimation(L"Needle", Needle_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		nt->SetScale(Vector2(0.9f, 0.9f));
		nt->PlayAnimation(L"Needle", true);
	}
	Needle::~Needle()
	{
	}
	void Needle::Initialize()
	{
		Item::Initialize();
	}
	void Needle::Update()
	{
		Item::Update();
	}
	void Needle::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Needle::OnCollisionEnter(Collider* other)
	{
		//
		GameObject* obj = other->GetOwner();
		Bazzi* player = dynamic_cast<Bazzi*>(obj);	// ¾ÈµÇ¸é nullptr
		if (player != nullptr)
		{
			player->SetActiveItem(Bazzi::eItem::Needle);
			Destroy(this);
		}


	}
	void Needle::OnCollisionStay(Collider* other)
	{
	}
	void Needle::OnCollisionExit(Collider* other)
	{
	}
	void Needle::Idle()
	{
	}
	void Needle::Use()
	{
	}
	void Needle::Extinct()
	{
	}
}