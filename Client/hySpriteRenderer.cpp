#include "hySpriteRenderer.h"
#include "hyTransform.h"
#include "hyGameObject.h"
// #include "hyCamera.h"

namespace hy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mScale(Vector2::One)
		//, mbAffectCamera(true)
		, mTexture(nullptr)
		//,mAlpha(1.0f)

		//<ī�޶�>
		//, mbAffectCamera(true)
		//, mTexture(nullptr)
		//, mAlpha(1.0f)			// ��ü�� �������� �ʰ� �ʱ�ȭ(0�� ����������� ����)
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

		if (mTexture == nullptr)									// mTexturer�� nullptr�̸� ���α׷��� ���峲
			return;													// �׷��� ���� nullptr�̸� �����ؼ� �Լ� ��ü�� ��������

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();

		// <ī�޶�>
		// if (mbAffectCamera)
		//	pos = Camera::CalculatePosition(pos);		// ī�޶� �̵��� �Ÿ���ŭ ����� ��	

		//if (mTexture->GetType() == eTextureType::Bmp)				// bmp ������ ��
		//{
		//	// ���� �۾�
		//	//if (mAlpha < 1.0f)				// ������ �־ �׷���� ��
		//	//{
		//	//	BLENDFUNCTION func = {};
		//	//	func.BlendOp = AC_SRC_OVER;
		//	//	func.BlendFlags = 0;
		//	//	func.AlphaFormat = AC_SRC_ALPHA;

		//	//	// 0.0f ~ 1.0f -> 0 ~ 255�� �ٲ���� ��
		//	//	int alpha = (int)(mAlpha * 255.0f);
		//	//	if (alpha <= 0)			
		//	//		alpha = 0;
		//	//	func.SourceConstantAlpha = alpha; // 0 ~ 255

		//	//	AlphaBlend(hdc, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)
		//	//		, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)
		//	//		, mTexture->GetWidth() * mScale.x
		//	//		, mTexture->GetHeight() * mScale.y
		//	//		, mTexture->GetHdc()
		//	//		, 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
		//	//		, func);
		//	//}
		//	//else
		//	//{	//  - (mTexture->GetWidth() * mScale.x / 2.0f) �÷��̾��� �߽��� �ƴ϶� �÷��̾��� 0,0�� ����Ű�� �ֱ� ������
		//	TransparentBlt(hdc, (int)pos.x //<ī�޶�>// - (mTexture->GetWidth() * mScale.x / 2.0f)
		//		, (int)pos.y //<ī�޶�>// - (mTexture->GetHeight() * mScale.y / 2.0f)
		//		, mTexture->GetWidth() * mScale.x
		//		, mTexture->GetHeight() * mScale.y
		//		, mTexture->GetHdc()
		//		, 0, 0, mTexture->GetWidth()
		//		, mTexture->GetHeight()
		//		, RGB(255, 0, 255));		//TransparentBlt�� 24��Ʈ
		//									//32��Ʈ ���İ��� ������ ���ĺ���
		//	//}
		//}

		//// TransparentBlt : ������ ��Ʈ���� ����ϴ� �� ���
		//// ����� ��Ʈ���� ���� ��ġ, ũ��, ������ ����, ����� ��ġ�� ���ڷ� 
		//// ����� ��Ʈ���� ������ �κ��� ��� X

		//else if (mTexture->GetType() == eTextureType::Png)		// png ������ ��
		//{
		//	//// ���� ���ϴ� �ȼ��� ����ȭ ��ų��
		//	//Gdiplus::ImageAttributes imageAtt = {};

		//	//// ����ȭ ��ų �ȼ� �� ����
		//	//imageAtt.SetColorKey(Gdiplus::Color(100,100,100)			// 0~255���� ���� ��� �����ϰ�(���ϴ� �� ����ȭ)
		//	//	, Gdiplus::Color(255,255,255));

		//	//Gdiplus::Graphics graphics(hdc);
		//	//graphics.DrawImage(mTexture->GetImage()
		//	//	, Gdiplus::Rect
		//	//	(
		//	//		(int)(pos.x - (mTexture->GetWidth() * mScale.x / 2.0f))
		//	//		, (int)(pos.y - (mTexture->GetHeight() * mScale.y / 2.0f))
		//	//		, (int)(mTexture->GetWidth() * mScale.x)
		//	//		, (int)(mTexture->GetHeight() * mScale.y)
		//	//	)
		//	//	, 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
		//	//	, Gdiplus::UnitPixel
		//	//	, &imageAtt);

		//	Gdiplus::Graphics graphics(hdc);
		//	graphics.DrawImage(mTexture->GetImage()
		//		, (int)(pos.x)//<ī�޶�>// - (mTexture->GetWidth() * mScale.x / 2.0f))
		//			, (int)(pos.y) //<ī�޶�>// - (mTexture->GetHeight() * mScale.y / 2.0f))
		//				, (int)(mTexture->GetWidth() * mScale.x)
		//				, (int)(mTexture->GetHeight() * mScale.y));
		//}

		GameObject* gameObj = GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		mTexture->Render(hdc
			, tr->GetPosition()
			, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, Vector2(0.0f, 0.0f)
			, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, Vector2::Zero
			, mScale
			//, mAlpha
		);
	}
}
