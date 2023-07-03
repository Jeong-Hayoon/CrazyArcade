#include "wzTime.h"

namespace wz
{
	LARGE_INTEGER Time::mCpuFrequency = {};			// 정적변수 초기화(LARGE_INTEGER가 구조체라서 {})
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time :: Initialize()
	{
		// CPU 고유 진동수를 가져온다.
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 시작됬을때 진동수를 가져온다.
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time :: Update()
	{
		QueryPerformanceCounter(&mCurFrequency);	// 현재 진동수를 가져온다

		float differenceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		// static_cast<float> -> c++ 스타일의 형변환

		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);	// 진동수의 차/CPU 고유진동수

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;		// Prev 진동수를 현재 진동수로 바꿔준다
	}

	void Time::Render(HDC hdc)				
	{
		static float timeCheck = 0.0f;		// 기존에 만든게 있으면 정적변수는 초기화는 스킵

		timeCheck += mDeltaTime;

		if (timeCheck >= 1.0f)				// 1초마다 그린다는 의미
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;				// 델타타임은 한번 순회하는데 걸린 시간, fps는 프레임 => 역수 취하면 1초 동안의 프레임 수가 나옴

			swprintf_s(szFloat, 50, L"fps : %f", fps);
			int strLen = wcsnlen_s(szFloat, 50);		// wcsnlen_s : wchar 2바이트 길이 구하는 함수

			TextOut(hdc, 10, 10, szFloat, strLen);	// TextOut : 화면에 글씨가 그려지는 함수

			timeCheck = 0.0f;					// 1초 초기화
		}
	}

}
