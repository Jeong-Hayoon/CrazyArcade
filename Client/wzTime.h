#pragma once
#include "CommonInclude.h"

// Delta time : 시간의 차이
// 성능이 다른 두 컴퓨터가 같은 속도로 이동을 하기 위해서는 걸린 시간을 측정하여 걸린시간 만큼 곱해줘야 함
// 정적변수를 사용하는 기준?

namespace wz
{
	class Time
	{
	public:
		static void Initialize();					
		static void Update();					
		static void Render(HDC hdc);		

		__forceinline static float DeltaTime() { return mDeltaTime; }		// 델타 타임을 가져오는 함수 

	private:			// LARGE_INTEGER - 구조체(16byte 정수)로 LowPart와 HIghPart로 나눠져 있음, 둘을 합치면 QuadPart
		static LARGE_INTEGER mCpuFrequency;			// CPU 고유 진동수
		static LARGE_INTEGER mPrevFrequency;			// 이전 진동수
		static LARGE_INTEGER mCurFrequency;			// 현재 진동수				=> 현재 진동수 - 이전 진동수 = 1프레임 진동수
		static float mDeltaTime;

		// union : 구조체와 함께 사용했을 때 공용체라 하여 메모리를 공유함
		// delta time : 한 프레임당 걸리는 시간
		// if(delta time >= ) 
	};
}

