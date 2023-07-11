#include "hySpriteRenderer.h"
#include "hyTransform.h"
#include "hyGameObject.h"

namespace hy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mScale(Vector2::One)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();

		///*Ellipse(hdc, 100 + pos.x, 100 + pos.y
		//	, 200 + pos.x, 200 + pos.y);*/

		//// �ε��ؿ� �̹��� �׸���
		//TransparentBlt(hdc, (int)pos.x, (int)pos.y					// �׸��� �׸��� ��ġ
		//	, mImage->GetWidth(), mImage->GetHeight()		// *2 �ϸ� ������ 2��
		//	, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		//// RGB(255, 0, 255) ������ ĥ���� �κ��� ����� 

		if (mTexture == nullptr)									// �̺κ� ����
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mTexture->GetType() == eTextureType::Bmp)				// bmp ������ ��
		{
			TransparentBlt(hdc, (int)pos.x, (int)pos.y
				, mTexture->GetWidth() * mScale.x, mTexture->GetHeight() * mScale.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}

		// TransparentBlt : ������ ��Ʈ���� ����ϴ� �� ���
		// ����� ��Ʈ���� ���� ��ġ, ũ��, ������ ����, ����� ��ġ�� ���ڷ� 
		// ����� ��Ʈ���� ������ �κ��� ��� X

		else if (mTexture->GetType() == eTextureType::Png)		// png ������ ��
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage(), (int)pos.x, (int)pos.y
				, (int)(mTexture->GetWidth() * mScale.x)
				, (int)(mTexture->GetHeight() * mScale.y));
		}
	}
}
