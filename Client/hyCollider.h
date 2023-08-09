#pragma once
#include "hyComponent.h"

namespace hy
{
	using namespace math;
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);		// �浹 ����
		void OnCollisionStay(Collider* other);		// �浹 ��
		void OnCollisionExit(Collider* other);		// �浹 ��������

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetPosition() { return mPosition; }
		void  SetPosition(Vector2 position) { mPosition = position; }

		UINT GetCollisionNumber() { return mCollisionNumber; }

	private:

		static UINT mCollisionCount;			// ������ȣ ������ ���� ����

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;

		UINT mCollisionNumber;					// �浹ü�� ������ ���� ��ȣ�� ����	
		bool mbIsCollision;						// �浹�ϴ°� ���� ���̰� �ϰ� �;��� �� ����
	};
}