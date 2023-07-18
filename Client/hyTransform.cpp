#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"

namespace hy
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mRotation(0.0f)

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
	}
	void Transform::Render(HDC hdc)
	{
	}
}
