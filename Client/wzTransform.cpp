#include "wzTransform.h"
#include "wzInput.h"
#include "wzTime.h"

namespace wz
{
	Transform::Transform()
		: Component(eComponentType::Transform)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
		if (Input::GetKey(eKeyCode::W))
		{
			mPosition.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			mPosition.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mPosition.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mPosition.x += 300.0f * Time::DeltaTime();
		}
	}
	void Transform::Render(HDC hdc)
	{
	}
}
