#pragma once
#include "hyComponent.h"
#include "hyImage.h"


namespace hy
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetImage(Image* image) { mImage = image; }

	private:
		Image* mImage;
	};
}
