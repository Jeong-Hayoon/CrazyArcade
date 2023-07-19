#pragma once
#include "CommonInclude.h"

namespace hy
{
#define LAYER_MAX (UINT)eLayerType::End

	union COlliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	using namespace enums;
	class CollisionManager
	{
	//public:
	//	static void Initialize();
	//	static void Update();
	//	static void Render(HDC hdc);
	//	static void Release();

	//private:
	//	static std::map<UINT64, bool> mCollisionMap;
	//	static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}

