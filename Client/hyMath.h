#pragma once

// hy::Math -> 이거 사용하려면 속성 들어가서 c++언어 표준을 20으로 변경해줘야 함

namespace hy::math // 위치를 표시할 구조체
{
	struct Vector2 // 크기, 방향을 가지고 있는 수학적 표시 방법(방향과 길이가 같으면 동일한 벡터) - 점으로 표현할 수도 있음
	{

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		float x;
		float y;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{

		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{

		}

		Vector2 operator+(const Vector2 other)
		{
			Vector2 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}

		Vector2 operator-(const Vector2 other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}

		Vector2 operator/(const float value)
		{
			Vector2 temp;
			temp.x = x / value;
			temp.y = y / value;
			return temp;
		}
	};
}

// 기저 벡터 : (1,0)과 (0,1)를 통해 다양한 벡터를 표시할 수 있음
// ? 초기화를 해줘야 하는 경우와 안해줘도 되는 경우 질문
