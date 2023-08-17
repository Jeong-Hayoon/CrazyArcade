#pragma once
#include"hyScene.h"
#include"hyTexture.h"


namespace hy
{
	class AlphaBlending : public GameObject
	{
	public:
		AlphaBlending();
		~AlphaBlending();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float mTime;
		Texture* mImage;
		BLENDFUNCTION func;
		int mAlpha;
		bool isTransparent;
	};
}

