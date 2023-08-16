#pragma once
class Win_Lose
{
};

#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Win_Lose : public GameObject
	{
	public:
		Win_Lose();
		virtual ~Win_Lose();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Win();

		void Lose();

		static bool GetWin_Lose_flag() { return Win_Lose_flag; }
		static void SetWin_Lose_flag(bool result) { Win_Lose_flag = result; }

	private:
		static bool Win_Lose_flag;
	};
}
