#pragma once
#include "hyGameObject.h"

namespace hy
{
	class GameStart : public GameObject
	{
	public:
		GameStart();
		virtual ~GameStart();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float GameTime;
		bool Start;
		bool Stop;


	};
}
