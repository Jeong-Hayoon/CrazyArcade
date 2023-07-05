#pragma once
#include "wzEntity.h"
#include "wzLayer.h"

namespace wz
{
	using namespace wz::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		std::vector<Layer> mLayers;
	};
}

