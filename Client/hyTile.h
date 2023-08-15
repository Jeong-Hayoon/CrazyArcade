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

			// floor 같이 충돌체가 없는 타일
			None,		
			// 부서지며 충돌체가 있는 타일
			Crack,
			// 부서지지는 않지만 충돌체는 있는 타입
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

