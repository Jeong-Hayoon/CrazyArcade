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

		// 몬스터 개수 관리
		static void SetMonsterQuantity(UINT Quantity) { MonsterQuantity = Quantity; }
		static void KillMonsterQuantity() { MonsterQuantity--; }
		static UINT GetMonsterQuantity() { return MonsterQuantity; }

		// 보스 개수 관리
		static void SetBossQuantity(UINT Quantity) { BossQuantity = Quantity; }
		static void KillBossQuantity() { BossQuantity--; }
		static UINT GetBossQuantity() { return BossQuantity; }

		// 맵 선택
		// 1 == ForestMap
		// 2 == IceMap
		// 3 == PirateMap
		static void SetActiveMap(UINT map) { ActiveMap = map; }
		static UINT GetActiveMap() { return ActiveMap; }

		// 플레이어 사망 시 true
		static void SetPlayerDead(bool dead) { PlayerDead = dead; }
		static bool GetPlayerDead() { return PlayerDead; }

	private:
		static std::map <std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		// 트리 자료구조
		// key value 구조로 이루어져 있따.
		// key는 데이터를 검색하는 용도
		// value 실제 우리가 써야할 데이터	

		static Bazzi* mBazzi;

		static UINT MonsterQuantity;
		static UINT BossQuantity;
		static UINT ActiveMap;
		static bool PlayerDead;
		

	};
}

