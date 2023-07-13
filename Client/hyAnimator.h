#pragma once
#include "hyComponent.h"
#include "hyAnimation.h"

namespace hy
{
	using namespace math;
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false);

		bool GetAffectedCamera() { return mbAffectedCamera; }
		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		bool mbLoop;
		bool mbAffectedCamera;
		float mAlpha;
	};
}


