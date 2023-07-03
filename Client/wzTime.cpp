#include "wzTime.h"

namespace wz
{
	LARGE_INTEGER Time::mCpuFrequency = {};			// �������� �ʱ�ȭ(LARGE_INTEGER�� ����ü�� {})
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time :: Initialize()
	{
		// CPU ���� �������� �����´�.
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷��� ���ۉ����� �������� �����´�.
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time :: Update()
	{
		QueryPerformanceCounter(&mCurFrequency);	// ���� �������� �����´�

		float differenceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		// static_cast<float> -> c++ ��Ÿ���� ����ȯ

		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);	// �������� ��/CPU ����������

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;		// Prev �������� ���� �������� �ٲ��ش�
	}

	void Time::Render(HDC hdc)				
	{
		static float timeCheck = 0.0f;		// ������ ����� ������ ���������� �ʱ�ȭ�� ��ŵ

		timeCheck += mDeltaTime;

		if (timeCheck >= 1.0f)				// 1�ʸ��� �׸��ٴ� �ǹ�
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;				// ��ŸŸ���� �ѹ� ��ȸ�ϴµ� �ɸ� �ð�, fps�� ������ => ���� ���ϸ� 1�� ������ ������ ���� ����

			swprintf_s(szFloat, 50, L"fps : %f", fps);
			int strLen = wcsnlen_s(szFloat, 50);		// wcsnlen_s : wchar 2����Ʈ ���� ���ϴ� �Լ�

			TextOut(hdc, 10, 10, szFloat, strLen);	// TextOut : ȭ�鿡 �۾��� �׷����� �Լ�

			timeCheck = 0.0f;					// 1�� �ʱ�ȭ
		}
	}

}
