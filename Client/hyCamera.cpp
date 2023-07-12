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
		mResolution.x = application.GetWidth();		// 해상도만큼 가로 세팅
		mResolution.y = application.GetHeight();	// 해상도만큼 세로 세팅
		mLookPosition = mResolution / 2.0f;			// 보는 위치를 창의 중앙으로 맞춤, -는 vector2의 오퍼레이터
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

		mDistance = mLookPosition - (mResolution / 2.0f);	// mDistance -> 윈도우 좌표계에서 카메라가 이동한 거리
	}
}

