#include "hyScene.h"
#include "hySpriteRenderer.h"

namespace hy
{
	Scene::Scene()
	{
		mLayers.resize((int)eLayerType::End);		// vector.resize : �ʱ�ȭ  - ������ �������� �� 0(���ϴ� ���� ����)���� �ʱ�ȭ�Ͽ� �� ������ ������
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		//for (size_t i = 0; i < mLayers.size(); i++)
		//{

		//}

		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}
}

