#pragma once
#include "CommonInclude.h"
#include "hyCollider.h"


namespace hy
{
#define LAYER_MAX (UINT)eLayerType::End

	union ColliderID
	{
		// 이미 충돌하고 있는지 아닌지 키 값
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
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		static void Clear();
		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);		// left와 right의 충돌 할건지 말건지
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);		//	몇번과 몇번이 충돌된 레이어인지
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}

