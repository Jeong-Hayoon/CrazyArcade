#pragma once
#include "hyGameObject.h"

namespace hy
{
	using namespace math;

	class Tile : public GameObject
	{
	public:

		enum class eType
		{
			/*Move,
			Fixed,*/

			// floor ���� �浹ü�� ���� Ÿ��
			None,		
			// �μ����� �浹ü�� �ִ� Ÿ��
			Crack,
			// �μ������� ������ �浹ü�� �ִ� Ÿ��
			Uncrushable,

			End,
		};


		static UINT mSelectedX;
		static UINT mSelectedY;

		Tile();
		~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetSourceTileIdx(int x, int y) { mSourceIndexX = x;  mSourceIndexY = y; }
		void SetTileIdx(int x, int y) { mIndexX = x;  mIndexY = y; }
		Vector2 GetSourceTileIdx() { return Vector2(mSourceIndexX, mSourceIndexY); }
		Vector2 GetTileIdx() { return Vector2(mIndexX, mIndexY); }
		void SetTile(int x, int y);
		
		eType GetType() { return mType; }
		void SetType(eType type) { mType = type; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		class SpriteRenderer* mSpriteRenderer;
		UINT mSourceIndexX;
		UINT mSourceIndexY;

		UINT mIndexX;
		UINT mIndexY;
		eType mType;

	};
}

