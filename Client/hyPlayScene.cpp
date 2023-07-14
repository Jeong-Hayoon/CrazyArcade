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
//#include "hyCamera.h"
#include "hyAnimator.h"
#include "hyTransform.h"

namespace hy
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		/*Texture* image = Resources::Load<Texture>(L"PlayBackGroundImgae"	
			, L"..\\Resources\\Image\\Bg\\play.bmp");	*/			
		
		//BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		//bgsr->SetImage(image);  
		//bgsr->SetScale(Vector2(1.5f, 1.338f));

		/*image = Resources::Load<Texture>(L"Smile"
			, L"..\\Resources\\Image\\Smile.png");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(0.2f, 0.2f));*/

		/*Player* player = object::Instantiate<Player>(eLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();*/

		// tr->SetPosition(Vector2(400.0f, 400.0f));
		//SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		//sr->SetImage(image);

		/*Animator* at = player->AddComponent<Animator>();
		at->CreateAnimation(L"FarmerIdle", image, Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f)
			, Vector2(0.0f, 0.0f), 6, 0.1f);
		at->CreateAnimation(L"FarmerRight", image, Vector2(0.0f, 32.0f), Vector2(16.0f, 32.0f)
			, Vector2(0.0f, 0.0f), 6, 0.1f);
		at->PlayAnimation(L"FarmerRight", true);*/
		//at->SetAffectedCamera(true);

		//Camera::SetTarget(player);

		Texture* image = Resources::Load<Texture>(L"Smile"
			, L"..\\Resources\\Image\\Characters\\Farmer\\farmer-girl-base.bmp");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();

		tr->SetPosition(Vector2(400.0f, 400.0f));

		image = Resources::Load<Texture>(L"Smile"
			, L"..\\Resources\\Image\\Player");

		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimation(L"FarmerIdle", image, Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 6);
		at->CreateAnimation(L"FarmerRight", image, Vector2(0.0f, 32.0f), Vector2(16.0f, 32.0f), 6);
		at->CreateAnimationFolder(L"Test", L"..\\Resources\\Image\\Player");
		at->PlayAnimation(L"Test", true);
		at->SetAffectedCamera(true);

	}
	void PlayScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"ForestMap");
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		/*wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"PlayScene");
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 700, 350, szFloat, strLen);

		Rectangle(hdc, 685, 400, 785, 500);*/
	}
}
