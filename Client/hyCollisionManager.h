#pragma once
#include "CommonInclude.h"
#include "hyCollider.h"


namespace hy
{
#define LAYER_MAX (UINT)eLayerType::End

	union ColliderID
	{
		// �̹� �浹�ϰ� �ִ��� �ƴ��� Ű ��
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
		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);		// left�� right�� �浹 �Ұ��� ������
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);		//	����� ����� �浹�� ���̾�����
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}

