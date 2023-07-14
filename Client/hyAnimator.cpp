#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"

// ��������Ʈ : �ִϸ��̼� �̹��� ������ �����
// ��������Ʈ ��Ʈ : ����� ������� ��Ƴ�����
// �ؽ�ó : �̹��� ���� ����ü
namespace hy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mAlpha(1.0f)
	{
	}
	Animator::~Animator()
	{
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

	void Animator::CreateAnimation(const std::wstring& name
		, Texture* texture
		, Vector2 leftTop
		, Vector2 size				// ��������Ʈ �ϳ��� ũ��
		, UINT spriteLength			// ����
		, Vector2 offset			// ���� ��ġ�� �ִϸ��̼� ���Ǵ� ��ġ�� ���� ���ϱ� ���� ���
		, float duration)			// �ִϸ��̼��� �Ѿ�� �ð�(����Ǵ� �ð� ����)
	{	
		Animation* animation = nullptr;
		animation = Resources::Find<Animation>(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
		Resources::Insert<Animation>(name, animation);
	}

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* image = Resources::Load<Texture>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		Texture* spriteSheet = Texture::Create(name, width * fileCount, height);

		int idx = 0;
		for (Texture* image : images)
		{
			BitBlt(spriteSheet->GetHdc(), width * idx, 0
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
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;		
	}
}



