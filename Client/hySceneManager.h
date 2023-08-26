#pragma once
#include "hyScene.h"

namespace hy
{
	class Bazzi;

	class SceneManager
	{
	public:

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		template<typename T>

		static T* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }

		static Bazzi* GetBazzi() { return mBazzi; }

		// ���� ���� ����
		static void SetMonsterQuantity(UINT Quantity) { MonsterQuantity = Quantity; }
		static void KillMonsterQuantity() { MonsterQuantity--; }
		static UINT GetMonsterQuantity() { return MonsterQuantity; }

		// ���� ���� ����
		static void SetBossQuantity(UINT Quantity) { BossQuantity = Quantity; }
		static void KillBossQuantity() { BossQuantity--; }
		static UINT GetBossQuantity() { return BossQuantity; }

		// �� ����
		// 1 == ForestMap
		// 2 == IceMap
		// 3 == PirateMap
		static void SetActiveMap(UINT map) { ActiveMap = map; }
		static UINT GetActiveMap() { return ActiveMap; }

		// �÷��̾� ��� �� true
		static void SetPlayerDead(bool dead) { PlayerDead = dead; }
		static bool GetPlayerDead() { return PlayerDead; }

	private:
		static std::map <std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		// Ʈ�� �ڷᱸ��
		// key value ������ �̷���� �ֵ�.
		// key�� �����͸� �˻��ϴ� �뵵
		// value ���� �츮�� ����� ������	

		static Bazzi* mBazzi;

		static UINT MonsterQuantity;
		static UINT BossQuantity;
		static UINT ActiveMap;
		static bool PlayerDead;
		

	};
}

