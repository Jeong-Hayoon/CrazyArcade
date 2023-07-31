#include "hyLayer.h"

namespace hy
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		// GameObject를 돌면서 obj가 멈춤 상태면 다음 인덱스로 넘어가고
		// 그게 아니라면 업데이트 함수 호출
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eState::Pause)
				continue;

			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		// GameObject를 돌면서 obj가 멈춤 상태면 다음 인덱스로 넘어가고
		// 그게 아니라면 렌더 함수 호출
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eState::Pause)
				continue;

			obj->Render(hdc);
		}

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			// 객체가 죽으면 이터레이터로 순회하면서 삭제
			if ((*iter)->GetState() == GameObject::eState::Dead)
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}


}
