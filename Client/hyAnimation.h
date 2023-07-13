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

		void Create(const std::wstring& name						// �ִϸ��̼� �̸�
			, class Texture* texture										// �̹���
			, Vector2 leftTop, Vector2 size, Vector2 offset		// ���� ���, ũ��, ������
			, UINT spriteLength, float duration);						// ��������Ʈ ����, ����

		void Reset();

		bool IsComplete() { return mbComplete; }			// �ִϸ��̼��� �Ϸ�Ǿ����� true ��ȯ
		void SetAnimator(Animator* animator) { mAnimator = animator; }		//mAnimator�� �ִϸ��̼��� ����ϴ� å���� ����


	private:
		Animator* mAnimator;
		Texture* mTexture;

		std::vector<Sprite> mSpriteSheet;				// �ִϸ��̼��� �������� ��Ÿ���� sprite ����ü ����
		int mIndex;												// �ִϸ��̼��� ���� ������ �ε���
		float mTime;											// �ִϸ��̼��� �ð�
		bool mbComplete;									// �ִϸ��̼��� �Ϸ�Ǿ����� ��Ÿ���� �÷���

	};
}
