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
#include "hyMonster.h"


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
		bg->GetComponent<Transform>()->SetPosition(Vector2(600.0f, 360.0f));	


		// �� �ʿ� ���� ȭ��
		Texture* ForestMap = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 362.0f));
		SpriteRenderer* forestmapsr= forestmap->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));

		// ���� �����¿� �ִϸ��̼�
		Bazzi* bazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		bazzi->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));
		bazzi->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(1050.0f,115.0f));

		// ������Ʈ ����
		Monster* monster = object::Instantiate<Monster>(eLayerType::Player);
		monster->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));

		Scene::Initialize();
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
