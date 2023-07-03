#include "wzCircle.h"
#include "wzTime.h"

namespace wz
{
	bool Circle::GetVisible( )			// 한줄짜리는 헤더에서 구현하는게 나음
	{
		return visible;
	}
	int Circle::GetDirection()
	{
		return direction;
	}
	void Circle::SetLocation(Vector2 value)
	{
		mLocation = value;
	}
	void Circle::SetVisible(bool value)
	{
		visible = value;
	}
	void Circle::SetDirection(int value)
	{
		direction = value;
	}
	void Circle::Shift()
	{
		if (direction == 0)			// y 감소
		{
			mLocation.y -= 300.0f * Time::DeltaTime();
		}
		else if (direction == 1)		// y 감소	, x 증가
		{
			mLocation.x += 300.0f * Time::DeltaTime();
			mLocation.y -= 300.0f * Time::DeltaTime();
		}
		else if (direction == 2)		// x 증가
		{
			mLocation.x += 300.0f * Time::DeltaTime();
		}
		else if (direction == 3)		// y 증가, x 증가
		{
			mLocation.x += 300.0f * Time::DeltaTime();
			mLocation.y += 300.0f * Time::DeltaTime();
		}
		else if (direction == 4)		// y 증가
		{
			mLocation.y += 300.0f * Time::DeltaTime();
		}
		else if (direction == 5)		// y 증가, x 감소
		{
			mLocation.x -= 300.0f * Time::DeltaTime();
			mLocation.y += 300.0f * Time::DeltaTime();
		}
		else if (direction == 6)		// x 감소
		{
			mLocation.x -= 300.0f * Time::DeltaTime();
		}
		else if (direction == 7)		// y 감소, x 감소
		{
			mLocation.x -= 300.0f * Time::DeltaTime();
			mLocation.y -= 300.0f * Time::DeltaTime();
		}
	}
	void Circle::Render(HDC mhdc)
	{
			Ellipse(mhdc, mLocation.x, mLocation.y, 70 + mLocation.x, 70 + mLocation.y);
	}
	void Circle::Update()
	{
		if (direction == -1)
		{
			direction = rand() % 8;
		}

		if (mLocation.x >= 1120)		// x가 감소하는거 필요
		{
			while (1)
			{
				direction = rand() % 8;
				if (direction == 5 || direction == 6 || direction == 7)
				{
					break;
				}
			}
		}

		if (mLocation.y >= 680)		// y가 감소하는거 필요
		{
			while (1)
			{
				direction = rand() % 8;
				if (direction == 0 || direction == 1 || direction == 7)
				{
					break;
				}
			}
		}

		if (mLocation.x <= 0)			// x가 증가하는거 필요
		{
			while (1)
			{
				direction = rand() % 8;
				if (direction == 1 || direction == 2 || direction == 3)
				{
					break;
				}
			};
		}

		if (mLocation.y <= 0)			// y가 증가하는거 필요
		{
			while (1)
			{
				direction = rand() % 8;
				if (direction == 3 || direction == 4 || direction == 5)
				{
					break;
				}
			}
		}

	}

	Vector2 Circle::GetLocation()
	{
		return mLocation;
	}

}
