#include "hyForestMap1.h"
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
#include "hyCollisionManager.h"


extern hy::Application application;
namespace hy
{
	ForestMap1::ForestMap1()
	{
	}
	ForestMap1::~ForestMap1()
	{
	}
	void ForestMap1::Initialize()
	{
		// ���� Ʋ
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2 + 10)));	

		// �� �ʿ� ���� ȭ��
		Texture* ForestMap1 = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap1 = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap1->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 410.0f));
		SpriteRenderer* forestmapsr= forestmap1->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap1);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));

		// ���� �����¿� �ִϸ��̼�
		Bazzi* forestbazzi1 = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = forestbazzi1->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(1022.0f, 163.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.8f, 0.8f));

		// ������Ʈ ����
		ForestMonster* forestmonster = object::Instantiate<ForestMonster>(eLayerType::Monster);
		forestmonster->GetComponent<Transform>()->SetPosition(Vector2(80.0f, 70.0f));

		//// �浹 ����
		//Collider* col = forestbazzi1->AddComponent<Collider>();
		//col->SetSize(Vector2(100.0f, 100.0f));
		////col->SetOffset(Vector2(10.0f, 10.0f));

		//col = forestmonster->AddComponent<Collider>();
		//col->SetSize(Vector2(100.0f, 100.0f));
		////col->SetOffset(Vector2(10.0f, 10.0f));
		//forestbazzitr = forestmonster->GetComponent<Transform>();

		//forestbazzitr->SetPosition(Vector2(940.0f, 360.0f));

		//// �÷��̾�� ���Ͱ� �浹
		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initialize();
	}
	void ForestMap1::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		{
			SceneManager::LoadScene(L"IceMap");
		}
	}
	void ForestMap1::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
