#pragma once
#include"hyScene.h"	
#include "hyLogo.h"


namespace hy
{
	class Texture;
	class Logo : public GameObject
	{
	public:
		Logo();
		~Logo();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


	private:
		Texture* mImage;
		float mTime;
		float mAlpha;
		bool IsTransparent;
	};
};

