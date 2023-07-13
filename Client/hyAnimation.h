#pragma once
#include "hyResource.h"

namespace hy
{
	using namespace math;
	class Texture;
	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		void Update();
		void Render(HDC hdc);

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Create(const std::wstring& name						// 애니메이션 이름
			, class Texture* texture										// 이미지
			, Vector2 leftTop, Vector2 size, Vector2 offset		// 왼쪽 상단, 크기, 오프셋
			, UINT spriteLength, float duration);						// 스프라이트 길이, 기한

		void Reset();

		bool IsComplete() { return mbComplete; }			// 애니메이션이 완료되었으면 true 반환
		void SetAnimator(Animator* animator) { mAnimator = animator; }		//mAnimator는 애니메이션을 재생하는 책임이 있음


	private:
		Animator* mAnimator;
		Texture* mTexture;

		std::vector<Sprite> mSpriteSheet;				// 애니메이션의 프레임을 나타내는 sprite 구조체 벡터
		int mIndex;												// 애니메이션의 현재 프레임 인덱스
		float mTime;											// 애니메이션의 시간
		bool mbComplete;									// 애니메이션이 완료되었음을 나타내는 플래그

	};
}
