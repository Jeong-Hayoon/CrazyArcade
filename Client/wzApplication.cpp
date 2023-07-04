#include "wzApplication.h"
#include "wzInput.h"
#include "wzTime.h"


// cpp ���Ͽ��� �Լ��� ���� �κ� �ۼ�

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
		mHwnd = hwnd;							// ��� ������ �ڵ� ����
		mHdc = GetDC(mHwnd);				// DC���� ��ȯ���ִ� �Լ�

		mWidth = 1600;
		mHeight = 900;

		RECT rect = { 0, 0, mWidth, mHeight };						
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);			// �������� ������ �����ϴ� �Լ�

		SetWindowPos(mHwnd																// ��� �޴��ٸ� ������ ũ�� �����ϴ� �Լ�
			, nullptr, 0, 0
			, rect.right - rect.left										// *** �̺κ� ����
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);

		// ������ �ػ� ������ ��Ʈ�� ����(��ȭ�� ����)
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);

		// ���� ������ ��Ʈ���� ����Ű�� DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ����				// *** �̺κ� ����
		HBITMAP defaultBitmap															// 24bit RGB�� ����ִ� �ڷ���
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);				// DC�� ���ο� ȭ��(��ȭ��) ����
		DeleteObject(defaultBitmap);													// *** �̺κ� ����


		Time :: Initialize();
		Input :: Initialize();
	
	}

	void Application::Run()						// �ѹ��� ���� �� - > ������
	{
		Update();
		Render();
	}

	void Application::Update()				// �����̴� ��ǥ�� ������Ŵ
	{
		Time::Update();
		Input::Update();

		// Ű�� �Է¹޾��� ��
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

	void Application::Render()			// ������ ��ǥ�� �ٽ� �׷���
	{
		Time::Render(mBackHdc);

		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

		//Rectangle(mHdc, 100, 100, 200, 200);
		Ellipse(mBackHdc, 100 + mPlayerPos.x, 100 + mPlayerPos.y
			, 200 + mPlayerPos.x, 200 + mPlayerPos.y);

		BitBlt(mHdc, 0, 0, mWidth, mHeight					// DC�� �׸��� �������ִ� �Լ�
			, mBackHdc, 0, 0, SRCCOPY);
	}

}

