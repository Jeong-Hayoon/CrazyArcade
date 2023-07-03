#pragma once
#include "CommonInclude.h"

// Delta time : �ð��� ����
// ������ �ٸ� �� ��ǻ�Ͱ� ���� �ӵ��� �̵��� �ϱ� ���ؼ��� �ɸ� �ð��� �����Ͽ� �ɸ��ð� ��ŭ ������� ��
// ���������� ����ϴ� ����?

namespace wz
{
	class Time
	{
	public:
		static void Initialize();					
		static void Update();					
		static void Render(HDC hdc);		

		__forceinline static float DeltaTime() { return mDeltaTime; }		// ��Ÿ Ÿ���� �������� �Լ� 

	private:			// LARGE_INTEGER - ����ü(16byte ����)�� LowPart�� HIghPart�� ������ ����, ���� ��ġ�� QuadPart
		static LARGE_INTEGER mCpuFrequency;			// CPU ���� ������
		static LARGE_INTEGER mPrevFrequency;			// ���� ������
		static LARGE_INTEGER mCurFrequency;			// ���� ������				=> ���� ������ - ���� ������ = 1������ ������
		static float mDeltaTime;

		// union : ����ü�� �Բ� ������� �� ����ü�� �Ͽ� �޸𸮸� ������
		// delta time : �� �����Ӵ� �ɸ��� �ð�
		// if(delta time >= ) 
	};
}

