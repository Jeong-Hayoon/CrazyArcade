#include "hyAnimation.h"
#include "hyTexture.h"
#include "hyAnimator.h"
#include "hyTime.h"
#include "hyTransform.h"
#include "hyGameObject.h"
#include "hyCamera.h"

namespace hy
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		if (mbComplete)			// 애니메이션이 완료되었는지 확인, 완료가 되었으면 코드가 반환됨
			return;

		// 완료되지 않았다면 
		// 델타 시간만큼 애니메이션의 시간 증가
		// 현재 프레임의 지속 시간이 애니메이션 시간보다 짧으면 
		// 애니메이션 시간을 0으로 재설정하고 애니메이션 인덱스 증가
		// 애니메이션의 인덱스가 스프라이트 시트의 크기보다 크거나 같으면 
		// 코드는 애니메이션의 완료 플래그를 true로 설정합니다.

	/*	frame = 8;
		currentFrame = 0
		currentFrame++;
		currentFrame = currentFrame % frame
		1 / 8 1
		2 / 8 2
		8 / 8 0*/

		mTime += Time::DeltaTime();			// 스톱워치
		if (mSpriteSheet[mIndex].duration < mTime)			// duration : 각 프레임이 유지되는 시간
		{
			mTime = 0.0f;

			if (mIndex < mSpriteSheet.size() - 1)			// size가 프레임의 총 개수
				mIndex++;
			else
				mbComplete = true;
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr)					// 이미지가 널값인지 체크
			return;

		// Transform 구성 요소에서 애니메이션 소유자의 Transform을 ​​가져옴
		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// 애니메이션이 카메라의 영향을 받는 경우
		if (mAnimator->GetAffectedCamera())
			pos = Camera::CalculatePosition(pos);

		// BLENDFUNCTION구조체 생성(알파블렌드 구글링 - 특정색을 제거해서 투명하게 만드는 작업)
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;			// 새 픽셀이 기존 픽셀과 혼합됨
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		// 0.0f ~ 1.0f -> 0 ~ 255
		int alpha = (int)(mAnimator->GetAlpha() * 255.0f);
		if (alpha <= 0)
			alpha = 0;
		func.SourceConstantAlpha = alpha; // 0 ~ 255

		AlphaBlend(hdc, (int)pos.x - (mSpriteSheet[mIndex].size.x / 2.0f) + mSpriteSheet[mIndex].offset.x
			, (int)pos.y - (mSpriteSheet[mIndex].size.y / 2.0f) + mSpriteSheet[mIndex].offset.y		//	 + mSpriteSheet[mIndex].offset.y..?	
			, mSpriteSheet[mIndex].size.x
			, mSpriteSheet[mIndex].size.y
			, mTexture->GetHdc()
			, mSpriteSheet[mIndex].leftTop.x
			, mSpriteSheet[mIndex].leftTop.y
			, mSpriteSheet[mIndex].size.x
			, mSpriteSheet[mIndex].size.y
			, func);
	}

	void Animation::Create(const std::wstring& name, Texture* texture
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLength, float duration)
	{
		mTexture = texture;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()			// 애니메이션을 재설정, .애니메이션의 시간, 인덱스,  mbComplete 플래그를 초기 값으로 설정
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

}
