#include "hyPirateMap.h"
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

namespace hy
{
	PirateMap::PirateMap()
	{
	}
	PirateMap::~PirateMap()
	{
	}
	void PirateMap::Initialize()
	{	
		// 게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImgae"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));

		// 각 맵에 따른 화면
		Texture* PirateMap = Resources::Load<Texture>(L"PirateMapImage"
			, L"..\\Resources\\Image\\Bg\\PirateNormalTile.bmp");
		BackGround* piratemap = object::Instantiate<BackGround>(eLayerType::Background);
		piratemap->GetComponent<Transform>()->SetPosition(Vector2(30.0f, 52.0f));
		SpriteRenderer* piratemapsr = piratemap->AddComponent<SpriteRenderer>();
		piratemapsr->SetImage(PirateMap);
		piratemapsr->SetScale(Vector2(1.0f, 0.9f));

		// 캐릭터
		Texture* Bazzi = Resources::Load<Texture>(L"BazziImage"
			, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(Bazzi);
		sr->SetScale(Vector2(0.8f, 0.8f));

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(987.0f, 125.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));

	}
	void PirateMap::Update()
	{
		Scene::Update();
	}
	void PirateMap::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
