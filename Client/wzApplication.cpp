#include "wzApplication.h"
#include "wzInput.h"
#include "wzTime.h"


// cpp 파일에는 함수의 정의 부분 작성

namespace wz
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
	{

	}

	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;							// 멤버 변수에 핸들 저장
		mHdc = GetDC(mHwnd);				// DC값을 반환해주는 함수

		mWidth = 1600;
		mHeight = 900;

		RECT rect = { 0, 0, mWidth, mHeight };						
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);			// 윈도우의 영역을 조절하는 함수

		SetWindowPos(mHwnd																// 상단 메뉴바를 제외한 크기 세팅하는 함수
			, nullptr, 0, 0
			, rect.right - rect.left										// *** 이부분 질문
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);

		// 윈도우 해상도 동일한 비트맵 생성(도화지 생성)
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);

		// 새로 생성한 비트맵을 가리키는 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		// 새로 생성한 비트맵과 DC를 서로 연결				// *** 이부분 질문
		HBITMAP defaultBitmap															// 24bit RGB만 들어있는 자료형
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);				// DC와 새로운 화면(도화지) 연결
		DeleteObject(defaultBitmap);													// *** 이부분 질문


		Time :: Initialize();
		Input :: Initialize();
	
	}

	void Application::Run()						// 한바퀴 도는 것 - > 프레임
	{
		Update();
		Render();
	}

	void Application::Update()				// 움직이는 좌표를 증가시킴
	{
		Time::Update();
		Input::Update();

		// 키를 입력받았을 대
		if (Input::GetKey(eKeyCode::W))
		{
			mPlayerPos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			mPlayerPos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mPlayerPos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mPlayerPos.x += 300.0f * Time::DeltaTime();
		}
			
	}

	void Application::Render()			// 움직인 좌표를 다시 그려줌
	{
		Time::Render(mBackHdc);

		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

		//Rectangle(mHdc, 100, 100, 200, 200);
		Ellipse(mBackHdc, 100 + mPlayerPos.x, 100 + mPlayerPos.y
			, 200 + mPlayerPos.x, 200 + mPlayerPos.y);

		BitBlt(mHdc, 0, 0, mWidth, mHeight					// DC간 그림을 복사해주는 함수
			, mBackHdc, 0, 0, SRCCOPY);
	}

}

