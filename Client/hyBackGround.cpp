#include "hyBackGround.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"

namespace hy
{
	BackGround::BackGround()
	{
	}
	BackGround::~BackGround()
	{
	}
	void BackGround::Initialize()
	{
	}

	void BackGround::Update()
	{
		GameObject::Update();
	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}