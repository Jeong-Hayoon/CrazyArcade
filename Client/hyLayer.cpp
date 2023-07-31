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
		// GameObject�� ���鼭 obj�� ���� ���¸� ���� �ε����� �Ѿ��
		// �װ� �ƴ϶�� ������Ʈ �Լ� ȣ��
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eState::Pause)
				continue;

			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		// GameObject�� ���鼭 obj�� ���� ���¸� ���� �ε����� �Ѿ��
		// �װ� �ƴ϶�� ���� �Լ� ȣ��
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
			// ��ü�� ������ ���ͷ����ͷ� ��ȸ�ϸ鼭 ����
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
