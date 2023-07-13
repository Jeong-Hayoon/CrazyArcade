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
		void SetAffectCamera(bool enable) { mbAffectCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

	private:
		//Gdiplus::Image* mImage;
		Texture* mTexture;		
		Vector2 mScale;					// �� ������Ʈ���� ũ�⸦ �ٸ��� �ϱ� ����
		bool mbAffectCamera;			// ī�޶��� ������ ������
		float mAlpha;						// 
	};
}
