#pragma once
#include "hyEntity.h"
#include "hyLayer.h"

namespace hy
{
	using namespace hy::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(eLayerType type, GameObject* gameObj)
		{
			mLayers[(int)type].AddGameObject(gameObj);
		}

		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }


	private:
		std::vector<Layer> mLayers;
	};
}

