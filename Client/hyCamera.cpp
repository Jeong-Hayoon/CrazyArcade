#include "hyCamera.h"
#include "hyApplication.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"

extern hy::Application application;

namespace hy
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;


	void Camera::Initalize()
	{
		mResolution.x = application.GetWidth();		// �ػ󵵸�ŭ ���� ����
		mResolution.y = application.GetHeight();	// �ػ󵵸�ŭ ���� ����
		mLookPosition = mResolution / 2.0f;			// ���� ��ġ�� â�� �߾����� ����, -�� vector2�� ���۷�����
	}

	void Camera::Update()
	{
		//if (Input::GetKey(eKeyCode::W))
		//{
		//	mLookPosition.y -= 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::A))
		//{
		//	mLookPosition.x -= 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::S))
		//{
		//	mLookPosition.y += 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::D))
		//{
		//	mLookPosition.x += 300.0f * Time::DeltaTime();
		//}

		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);	// mDistance -> ������ ��ǥ�迡�� ī�޶� �̵��� �Ÿ�
	}
}

