#include "wzApplication.h"
#include "wzInput.h"
#include "wzTime.h"
#include <cstdlib> // rand(), srand()
#include <ctime> / /time()
#include "wzCircle.h"


// cpp ���Ͽ��� �Լ��� ���� �κ� �ۼ�

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
		mHwnd = hwnd;						// ��� ������ �ڵ� ����
		mHdc = GetDC(mHwnd);				// DC���� ��ȯ���ִ� �Լ�

		Time :: Initialize();
		Input :: Initialize();
		
		for(int i = 0; i < 256; i++)
		{
			circle[i] = {};
		}

		circle[0].SetVisible(true);

		srand((unsigned int)time(NULL));
	}

	void Application::Run()					// �ѹ��� ���� �� - > ������
	{
		Update();
		Render();
	}

	void Application::Update()				// �����̴� ��ǥ�� ������Ŵ
	{
		Time::Update();
		// Input::Update();

	/*	if (Input::GetKey(eKeyCode::W))			// Ű�� �Է¹޾��� ��
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
			circle[i].Update();			// ���� ó��(���� �ε����� ��)
			circle[i].Shift();
		}		
	}

	void Application::Render()			// ������ ��ǥ�� �ٽ� �׷���
	{
		//Time::Render(mHdc);

		////Rectangle(mHdc, 100, 100, 200, 200); �簢�� �׸���
		//Ellipse(mHdc, mPlayerPos[i].x, mPlayerPos[i].y, 100 + mPlayerPos[i].x, 100 + mPlayerPos[i].y);

		static float Counting = 0.0f;
		static int num = 1;
		
		Counting += Time::DeltaTime();
	
		if (Counting > 1.f && num < 256)				// num�� 256�� �Ѿ������ �迭�� ����
		{
			circle[num].SetVisible(true);
			circle[num].SetLocation(Vector2(rand() % 645, rand() % 1090));		// ��ġ ���� �����ָ� �ٰ��� ���̶� ���ĺ���
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

