#include "hyCollider.h"
#include "hyTransform.h"
#include "hyGameObject.h"

//충돌을 하기 위한 하나의 도형
namespace hy
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:Component(eComponentType::Collider)
		, mSize(Vector2::Zero)
		, mOffset(Vector2::Zero)
		, mCollisionNumber(-1)
		, mbIsCollision(false)
	{
		mCollisionNumber = mCollisionCount;	
		mCollisionCount++;
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPosition = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		// 카메라
		//pos = Camera::CalculatePosition(pos);
		
		// 디폴트 브러쉬 - 스톡 오브젝트
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		// 선을 바꾸는 건 펜 브러쉬
		/*HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);*/

		HPEN pen = NULL;
		if (mbIsCollision)			// 충돌되어있는 상태라면(충돌이 된 상태인지 체크)
		{
			pen = CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
		}
		else
		{
			pen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mSize.x, pos.y + mSize.y);

		SelectObject(hdc, oldBrush);
		DeleteObject(transparentBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)		// 막 빠져나갔을 때(충돌 X)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}
