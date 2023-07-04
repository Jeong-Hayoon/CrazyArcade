#include "wzApplication.h"
#include "wzInput.h"
#include "wzTime.h"
#include <cstdlib> // rand(), srand()
#include <ctime> / /time()
#include "wzCircle.h"


// cpp 파일에는 함수의 정의 부분 작성

namespace wz
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{

	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;						// 멤버 변수에 핸들 저장
		mHdc = GetDC(mHwnd);				// DC값을 반환해주는 함수

		Time :: Initialize();
		Input :: Initialize();
		
		for(int i = 0; i < 256; i++)
		{
			circle[i] = {};
		}

		circle[0].SetVisible(true);

		srand((unsigned int)time(NULL));
	}

	void Application::Run()					// 한바퀴 도는 것 - > 프레임
	{
		Update();
		Render();
	}

	void Application::Update()				// 움직이는 좌표를 증가시킴
	{
		Time::Update();
		// Input::Update();

	/*	if (Input::GetKey(eKeyCode::W))			// 키를 입력받았을 대
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
		}*/
		
		for(int i = 0; i < 256; i++)
		{
			circle[i].Update();			// 예외 처리(벽에 부딪혔을 때)
			circle[i].Shift();
		}		
	}

	void Application::Render()			// 움직인 좌표를 다시 그려줌
	{
		//Time::Render(mHdc);

		////Rectangle(mHdc, 100, 100, 200, 200); 사각형 그리기
		//Ellipse(mHdc, mPlayerPos[i].x, mPlayerPos[i].y, 100 + mPlayerPos[i].x, 100 + mPlayerPos[i].y);

		static float Counting = 0.0f;
		static int num = 1;
		
		Counting += Time::DeltaTime();
	
		if (Counting > 1.f && num < 256)				// num이 256을 넘어버리면 배열이 터짐
		{
			circle[num].SetVisible(true);
			circle[num].SetLocation(Vector2(rand() % 645, rand() % 1090));		// 위치 지정 안해주면 다같은 곳이라 겹쳐보임
			num++;
			Counting = 0.0f;
		}


		for(int i = 0; i < 256; i++)
		{
			if (circle[i].GetVisible() == true)
			{
				circle[i].Render(mHdc);
			}
		}
	}

}

