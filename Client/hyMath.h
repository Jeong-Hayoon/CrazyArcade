#pragma once
#include <cmath>

// hy::Math -> 이거 사용하려면 속성 들어가서 c++언어 표준을 20으로 변경해줘야 함

namespace hy::math // 위치를 표시할 구조체
{
	#define PI 3.141592f


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

		Vector2 operator -()
		{
			return Vector2(-x, -y);
		}


		Vector2 operator-(const Vector2 other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}

		Vector2 operator*(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x * other.x;
			temp.y = y * other.y;

			return temp;
		}

		Vector2 operator*(const float& value)
		{
			Vector2 temp;
			temp.x = x * value;
			temp.y = y * value;

			return temp;
		}

		Vector2 operator/(const float& value)
		{
			Vector2 temp;

			temp.x = x / value;
			temp.y = y / value;

			return temp;
		}

		Vector2& operator +=(const Vector2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vector2& operator -=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vector2& operator *=(const float& value)
		{
			x *= value;
			y *= value;

			return *this;
		}	

		bool operator ==(const Vector2& other)
		{
			return (x == other.x && y == other.y);
		}


		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 normalize()
		{
			float len = length();
			x /= len;
			y /= len;

			return *this;
		}
	};

	inline Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.f) * PI;
		vector.normalize();
		float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
		float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

		return Vector2(x, y);
	}

	inline float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline float Cross(Vector2 v1, Vector2 v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
}

// 기저 벡터 : (1,0)과 (0,1)를 통해 다양한 벡터를 표시할 수 있음
