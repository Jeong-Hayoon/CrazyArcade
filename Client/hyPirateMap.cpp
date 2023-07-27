#include "hyPirateMap.h"
#include "hyPlayScene.h"
#include "hyTitleScene.h"
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
#include "hyPirateMonster.h"


extern hy::Application application;

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
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));

		// 각 맵에 따른 화면
		Texture* PirateMap = Resources::Load<Texture>(L"PirateMapImage"
			, L"..\\Resources\\Image\\Bg\\PirateNormalTile.bmp");
		BackGround* piratemap = object::Instantiate<BackGround>(eLayerType::Background);
		piratemap->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 402.0f));

		SpriteRenderer* piratemapsr = piratemap->AddComponent<SpriteRenderer>();
		piratemapsr->SetImage(PirateMap);
		piratemapsr->SetScale(Vector2(1.0f, 0.9f));

		// 배찌 상하좌우 애니메이션
		Bazzi* piratebazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		piratebazzi->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(1022.0f, 163.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));

		// 피라테 몬스터
		PirateMonster* piratemonster = object::Instantiate<PirateMonster>(eLayerType::Monster);
		piratemonster->GetComponent<Transform>()->SetPosition(Vector2(80.0f, 70.0f));

		Scene::Initialize();
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
