#pragma once
#include "CommonInclude.h" 
#include <cstdlib> // rand(), srand()
#include <ctime> //time()

namespace wz
{
	using namespace math;
	class Circle
	{
	public:
		Circle()
			: visible(0)
			, direction(-1)
		{

		}

		~Circle()
		{

		}

		void Update();
		Vector2 GetLocation();
		bool GetVisible();
		int GetDirection();

		void SetLocation(Vector2 value);
		void SetVisible(bool value);
		void SetDirection(int value);
		void Shift();
		void Render(HDC mhdc);

	private:
		Vector2 mLocation;
		bool visible;
		int direction;
	};
}


