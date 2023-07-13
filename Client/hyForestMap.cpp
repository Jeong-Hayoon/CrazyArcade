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
		// ���� Ʋ
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));

		// �� �ʿ� ���� ȭ��
		Texture* ForestMap = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap->GetComponent<Transform>()->SetPosition(Vector2(30.0f, 52.0f));
		SpriteRenderer* forestmapsr= forestmap->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));

		// ĳ����
		Texture* Bazzi = Resources::Load<Texture>(L"BazziImage"
			, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(Bazzi);
		sr->SetScale(Vector2(0.8f, 0.8f));

		std::wstring name = player->GetName(); 

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(987.0f,125.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));



	}
	void ForestMap::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		{
			SceneManager::LoadScene(L"IceMap");
		}
	}
	void ForestMap::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
