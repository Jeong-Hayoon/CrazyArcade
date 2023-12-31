#pragma once
#include "hyComponent.h"
#include "hyTexture.h"


namespace hy
{
	using namespace math;
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetImage(Texture* image) { mTexture = image; }
		void SetScale(Vector2 scale) { mScale = scale; }
		//<카메라>
		//void SetAffectCamera(bool enable) { mbAffectCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }
		void SetTile(int x, int y) { mbTile = true; mTileIndexX = x; mTileIndexY = y; }


	private:
		//Gdiplus::Image* mImage;
		Texture* mTexture;		
		Vector2 mScale;					// 각 오브젝트마다 크기를 다르게 하기 위함

		// <카메라>
		//bool mbAffectCamera;			// 카메라의 영향을 빋는지

		float mAlpha;						

		// 타일의 인덱스
		bool mbTile;
		int mTileIndexX;
		int mTileIndexY;
	};
}
