#include "hyIceMap.h"
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


namespace hy
{
	IceMap::IceMap()
	{
	}
	IceMap::~IceMap()
	{
	}
	void IceMap::Initialize()
	{
		// 게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImgae"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));

		// 각 맵에 따른 화면
		Texture* IceMap = Resources::Load<Texture>(L"IceMapImage"
			, L"..\\Resources\\Image\\Bg\\ICETILE.bmp");
		BackGround* icemap = object::Instantiate<BackGround>(eLayerType::Background);
		icemap->GetComponent<Transform>()->SetPosition(Vector2(30.0f, 52.0f));
		SpriteRenderer* icemapsr = icemap->AddComponent<SpriteRenderer>();
		icemapsr->SetImage(IceMap);
		icemapsr->SetScale(Vector2(1.0f, 0.90f));

		// 캐릭터
		Texture* Bazzi = Resources::Load<Texture>(L"BazziImage"
			, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));

		// 애니메이션
		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimation(L"BazziIdle", Bazzi, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f));
		at->PlayAnimation(L"BazziIdle", true);

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(987.0f, 125.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));

		std::wstring name = player->GetName();

		// 아이스 몬스터(상하좌우, 사망 애니메이션)
		/*Player* IceMonster = object::Instantiate<Player>(eLayerType::Player);
		IceMonster->GetComponent<Transform>()->SetPosition(Vector2(120.0f, 70.0f));

		Animator* mt = IceMonster->AddComponent<Animator>();
		mt->CreateAnimationFolder(L"IceMonsterUp", L"..\\Resources\\Image\\Monster\\\\Up");
		mt->CreateAnimationFolder(L"IceMonsterDown", L"..\\Resources\\Image\\Monster\\\\Down");
		mt->CreateAnimationFolder(L"IceMonsterRight", L"..\\Resources\\Image\\Monster\\\\Right");
		mt->CreateAnimationFolder(L"IceMonsterLeft", L"..\\Resources\\Image\\Monster\\\\Left");
		mt->CreateAnimationFolder(L"IceMonsterDie", L"..\\Resources\\Image\\Monster\\\\Die");*/

	}
	void IceMap::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"PirateMap");
		}
	}
	void IceMap::Render(HDC hdc)
	{
		Scene::Render(hdc);


	}
}
