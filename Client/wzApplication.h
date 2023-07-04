#pragma once
#include "CommonInclude.h" 
#include "wzCircle.h"

// 헤더에는 변수, 함수의 선언부만 작성(간단한 경우에는 헤더에서 구현, 많고 복잡한 경우에는 cpp쪽에 구현)

namespace wz			// namespace가 다르면 클래스 이름이 같아도 사용할 수 있음
{
	using namespace math;
	class Application	// 메인에서 생성된 핸들을 클래스에 저장해서 보관(윈도우 자체의 정보를 들고 있는 클래스)
	{
	public:				// 함수 지정 후 우클릭 - 빠른 작업 및 리팩터링 - 선언 정의 만들기
		Application();
		~Application();

		void Initialize(HWND hwnd);		// 멤버변수에 핸들을 넣기 위해 초기화 함수 인자에 핸들 값을 넣어줌
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;
		Vector2 mPlayerPos;				// 좌표 저장할 변수
		Circle circle[256];
	};
}
