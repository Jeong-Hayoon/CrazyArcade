#include "hyScene.h"
#include "hySpriteRenderer.h"

namespace hy
{
	Scene::Scene()
	{
		mLayers.resize((int)eLayerType::End);		// vector.resize : 초기화  - 지정한 범위까지 다 0(원하는 값도 가능)으로 초기화하여 다 접근이 가능함
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

