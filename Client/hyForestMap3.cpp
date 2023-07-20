#include "hyForestMap3.h"
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
#include "hyForestMonster.h"

extern hy::Application application;
namespace hy
{
	ForestMap3::ForestMap3()
	{
	}
	ForestMap3::~ForestMap3()
	{
	}
	void ForestMap3::Initialize()
	{
		// 게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2 + 10)));

		// 각 맵에 따른 화면
		Texture* ForestMap3 = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap3 = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap3->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 410.0f));
		SpriteRenderer* forestmapsr = forestmap3->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap3);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));

		// 배찌 상하좌우 애니메이션
		Bazzi* forestbazzi3 = object::Instantiate<Bazzi>(eLayerType::Player);
		forestbazzi3->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(1022.0f, 163.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));

		// 포레스트 몬스터
		ForestMonster* forestmonster = object::Instantiate<ForestMonster>(eLayerType::Player);
		forestmonster->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));

		Scene::Initialize();
	}
	void ForestMap3::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"IceMap");
		}
	}
	void ForestMap3::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
