#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"

// 스프라이트 : 애니메이션 이미지 파일의 한장면
// 스프라이트 시트 : 한장면 한장면을 모아놓은것
// 텍스처 : 이미지 파일 그자체
namespace hy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mAlpha(1.0f)
		, mScale(Vector2::One)
	{
	}
	Animator::~Animator()
	{
		for (auto iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && mbLoop)
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
			mActiveAnimation->Render(hdc);
	}

	Animation* Animator::CreateAnimation(const std::wstring& name
		, Texture* texture
		, Vector2 leftTop
		, Vector2 size				// 스프라이트 하나의 크기
		, UINT spriteLength			// 개수
		, Vector2 offset			// 실제 위치와 애니메이션 사용되는 위치를 따로 구하기 위해 사용
		, float duration)			// 애니메이션이 넘어가는 시간(실행되는 시간 제외)
	{	
		SetName(name);
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)		
		{
			return animation;
		}

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
	}

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, Vector2 offset, float duration)
	{
		SetName(name);

		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;
			
		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};

		eTextureType texturetype = eTextureType::None;

		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* image = Resources::Load<Texture>(fileName, fullName);

			texturetype = image->GetType();

			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		std::wstring spriteSheetName = name + L"SpriteSheet";

		Texture* spriteSheet = Texture::Create(spriteSheetName, width * fileCount, height);

		spriteSheet->SetType(texturetype);

		int idx = 0;
		for (Texture* image : images)
		{
			BitBlt(spriteSheet->GetHdc()
				, (width * idx) + ((width - image->GetWidth()) / 2.0f)
				, 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		CreateAnimation(name
			, spriteSheet, Vector2(0.0f, 0.0f)
			, Vector2(width, height), fileCount
			, offset, duration);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		SetName(name);

		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	// 인자로 들어온 name을 통해 애니메이션을 찾고 만들어져 있는 애니메이션이
	// 존재한다면 mActiveAnimation에 애니메이션을 넣어주는 함수
	// 만들어진 애니메이션이 없다면 return
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		SetName(name);

		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;
		/*if(animation!=mActiveAnimation)
		{
			mActiveAnimation = animation;
			mActiveAnimation->Reset();
		}*/
		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;		
	}
}



