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

		// 1P, 2P ����
		static void SetSelectSoloPlayer(bool solo) { SelectSoloPlayer = solo; }
		static bool GetSelectSoloPlayer() { return SelectSoloPlayer; }

		static void SetSelectMultiPlayer(bool multi) { SelectMultiPlayer = multi; }
		static bool GetSelectMultiPlayer() { return SelectMultiPlayer; }

		// Stage ǥ��
		// 0 = Forestmap1	/ 1 = Forestmap2	/ 2 = Forestmap3
		// 3 = Icemap1		/ 4 = Icemap2		/ 5 = Icemap3
		// 6 = Piratemap1	 / 7 = Piratemap2	/ 8 = Piratemap3
		static void SetActiveStage(int stage) { ActiveStage = stage; }
		static int GetActiveStage() { return ActiveStage; }

		int GetStageData(int stage, int row, int col) { return StageData[stage][row][col; }
		void SetStageData(int stage, int row, int col, int value) { StageData[stage][row][col] = value; }


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
		static bool SelectSoloPlayer;
		static bool SelectMultiPlayer;
		static int ActiveStage;

		// 0 - �ٴ� / 1 - Crack / 2 - Uncrushable
		/*static int Forest_1_Data[13][15];
		static int Forest_2_Data[13][15];
		static int Forest_3_Data[13][15];

		static int Ice_1_Data[13][15];
		static int Ice_2_Data[13][15];
		static int Ice_3_Data[13][15];

		static int Pirate_1_Data[13][15];
		static int Pirate_2_Data[13][15];
		static int Pirate_3_Data[13][15];*/

		static int StageData[9][13][15];

	};
}

