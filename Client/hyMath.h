#pragma once

// hy::Math -> �̰� ����Ϸ��� �Ӽ� ���� c++��� ǥ���� 20���� ��������� ��

namespace hy::math // ��ġ�� ǥ���� ����ü
{
	struct Vector2 // ũ��, ������ ������ �ִ� ������ ǥ�� ���(����� ���̰� ������ ������ ����) - ������ ǥ���� ���� ����
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

// ���� ���� : (1,0)�� (0,1)�� ���� �پ��� ���͸� ǥ���� �� ����
// ? �ʱ�ȭ�� ����� �ϴ� ���� �����൵ �Ǵ� ��� ����
