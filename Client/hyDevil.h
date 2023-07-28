#pragma once
#include "hyGameObject.h"

//�ӵ� �ִ� ������
namespace hy
{
	class Devil : public GameObject
	{
		Devil();
		virtual ~Devil();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

