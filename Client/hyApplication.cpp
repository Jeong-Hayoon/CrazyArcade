#include "hyApplication.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyTitleScene.h"
#include "hySceneManager.h"
//#include "yaCamera.h"

// cpp ���Ͽ��� �Լ��� ���� �κ� �ۼ�

namespace hy
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

		mWidth = 1200;
		mHeight = 800;

		RECT rect = { 0, 0, mWidth, mHeight };						
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);		// �������� ������ �����ϴ� �Լ�

		SetWindowPos(mHwnd		// ��� �޴��ٸ� ������ ũ�� �����ϴ� �Լ�
			, nullptr, 0, 0
			, rect.right - rect.left								
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);

		// ������ �ػ� ������ ��Ʈ�� ����(��ȭ�� ����)
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);

		// ���� ������ ��Ʈ���� ����Ű�� DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ����						
		HBITMAP defaultBitmap												// 24byte RGB�� ����ִ� �ڷ���
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);	// DC�� ���ο� ȭ��(��ȭ��) ����
		DeleteObject(defaultBitmap);										// (�⺻ ��Ʈ���� ����� - ������ �ȵǴ� ���� �츮�� ���ϴ� ũ�Ⱑ �ƴϹǷ� ��ü)
																			// �⺻ ��Ʈ���� �ʿ�����Ƿ� ����
		Time :: Initialize(); 
		Input :: Initialize();
		// 	Camera::Initalize();

		SceneManager::Initialize();
	}

	void Application::Run()				// �ѹ��� ���� �� - > ������
	{
		Update();
		Render();
	}

	void Application::Update()		// �����̴� ��ǥ�� ������Ŵ
	{
		Time::Update();
		Input::Update();
		//	Camera::Update();

		SceneManager::Update();

		//// Ű�� �Է¹޾��� ��
		//if (Input::GetKey(eKeyCode::W))
		//{
		//	mPlayerPos.y -= 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::A))
		//{
		//	mPlayerPos.x -= 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::S))
		//{
		//	mPlayerPos.y += 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::D))
		//{
		//	mPlayerPos.x += 300.0f * Time::DeltaTime();
		//}
			
	}

	void Application::Render()		// ������ ��ǥ�� �ٽ� �׷���
	{
		//Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);		// +1, -1�� ������ â�� ���̴� ���� ����� ���� 
		//Time::Render(mBackHdc);													// �׸��� mBackHdc�� �׸��� 

		// ���
		HBRUSH brush = CreateSolidBrush(RGB(125, 125, 125));				// �귯�� ����
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, brush);			// ���� �귯���� ���ư��� ��
		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);
		SelectObject(mBackHdc, oldBrush);				// ��ü ����
		DeleteObject(brush);			// �ݳ�

		Time::Render(mBackHdc);

		SceneManager::Render(mBackHdc);

		//Rectangle(mHdc, 100, 100, 200, 200);
		/*	Ellipse(mBackHdc, 100 + mPlayerPos.x, 100 + mPlayerPos.y
			, 200 + mPlayerPos.x, 200 + mPlayerPos.y);*/

		BitBlt(mHdc, 0, 0, mWidth, mHeight				// DC�� �׸��� �������ִ� �Լ�
			, mBackHdc, 0, 0, SRCCOPY);					// mHdc�� mBackHdc�� ����
	}
}

