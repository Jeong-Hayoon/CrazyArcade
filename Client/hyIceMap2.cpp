#include "hyIceMap2.h"
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
#include "hyPirateMonster.h"



extern hy::Application application;

namespace hy
{
	IceMap2::IceMap2()
	{
	}
	IceMap2::~IceMap2()
	{
	}
	void IceMap2::Initialize()
	{
		//게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImgae"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2 + 10)));


		// 각 맵에 따른 화면
		Texture* IceMap1 = Resources::Load<Texture>(L"IceMapImage"
			, L"..\\Resources\\Image\\Bg\\ICETILE.bmp");
		BackGround* icemap1 = object::Instantiate<BackGround>(eLayerType::Background);
		icemap1->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 410.0f));
		SpriteRenderer* icemapsr = icemap1->AddComponent<SpriteRenderer>();
		icemapsr->SetImage(IceMap1);
		icemapsr->SetScale(Vector2(1.0f, 0.90f));

		//배찌 상하좌우 애니메이션
		Bazzi* icebazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		icebazzi->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(1022.0f, 163.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));

		/*std::wstring name = player->GetName();*/

		// 아이스 몬스터
		PirateMonster* icemonster = object::Instantiate<PirateMonster>(eLayerType::Player);
		icemonster->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));

		Scene::Initialize();

	}
	void IceMap2::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"PirateMap");
		}
	}
	void IceMap2::Render(HDC hdc)
	{
		Scene::Render(hdc);


	}
}
