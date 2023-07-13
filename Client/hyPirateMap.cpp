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
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImgae"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.338f));

		/*image = Resources::Load<Texture>(L"Smile"
			, L"..\\Resources\\Image\\Smile.png");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(0.2f, 0.2f));*/

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
