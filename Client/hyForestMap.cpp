#include "hyForestMap.h"
#include "hyPlayScene.h"
#include "hyTitleScene.h"
#include "hyPlayer.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBackGround.h"
#include "hyTransform.h"
#include "hyAnimator.h"
#include "hyBazzi.h"


namespace hy
{
	ForestMap::ForestMap()
	{
	}
	ForestMap::~ForestMap()
	{
	}
	void ForestMap::Initialize()
	{
		// 게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));

		// 각 맵에 따른 화면
		Texture* ForestMap = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap->GetComponent<Transform>()->SetPosition(Vector2(30.0f, 52.0f));
		SpriteRenderer* forestmapsr= forestmap->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));

		// 배찌 상하좌우 애니메이션
		Texture* Bazzi = Resources::Load<Texture>(L"Bazzi"
			, L"..\\Resources\\Image\\Bazzi\\Bazzi.bmp");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));
	//*SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
	//	sr->SetImage(Bazzi);
	//	sr->SetScale(Vector2(0.8f, 0.8f));*/

	//	std::wstring name = player->GetName();

		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimation(L"BazziIdle", Bazzi, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4 , Vector2(0.0f, 0.0f), 0.4f);
		at->CreateAnimation(L"BazziUp", Bazzi, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDown", Bazzi, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRight", Bazzi, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeft", Bazzi, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDie", Bazzi, Vector2(0.0f, 300.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f); 

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(987.0f,125.0f));

		// 포레스트 몬스터(상하좌우, 사망 애니메이션)
		Player* ForestMonster= object::Instantiate<Player>(eLayerType::Player);
		ForestMonster->GetComponent<Transform>()->SetPosition(Vector2(120.0f, 70.0f));

		Animator* mt = ForestMonster->AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMosterUp", L"..\\Resources\\Image\\Monster\\Forest\\Up");
		mt->CreateAnimationFolder(L"ForestMosterDown", L"..\\Resources\\Image\\Monster\\Forest\\Down");
		mt->CreateAnimationFolder(L"ForestMosterRight", L"..\\Resources\\Image\\Monster\\Forest\\Right");
		mt->CreateAnimationFolder(L"ForestMosterLeft", L"..\\Resources\\Image\\Monster\\Forest\\Left");
		mt->CreateAnimationFolder(L"ForestMonsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die"); 

	}
	void ForestMap::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"IceMap");
		}
	}
	void ForestMap::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
