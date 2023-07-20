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

		void OnCollisionEnter(Collider* other);		// 충돌 시작
		void OnCollisionStay(Collider* other);		// 충돌 중
		void OnCollisionExit(Collider* other);		// 충돌 빠져나감

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetPosition() { return mPosition; }
		UINT GetCollisionNumber() { return mCollisionNumber; }

	private:

		static UINT mCollisionCount;

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;

		UINT mCollisionNumber;
		bool mbIsCollision;
	};
}