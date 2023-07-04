#pragma once
#include "CommonInclude.h" 
#include "wzCircle.h"

// ������� ����, �Լ��� ����θ� �ۼ�(������ ��쿡�� ������� ����, ���� ������ ��쿡�� cpp�ʿ� ����)

namespace wz			// namespace�� �ٸ��� Ŭ���� �̸��� ���Ƶ� ����� �� ����
{
	using namespace math;
	class Application	// ���ο��� ������ �ڵ��� Ŭ������ �����ؼ� ����(������ ��ü�� ������ ��� �ִ� Ŭ����)
	{
	public:				// �Լ� ���� �� ��Ŭ�� - ���� �۾� �� �����͸� - ���� ���� �����
		Application();
		~Application();

		void Initialize(HWND hwnd);		// ��������� �ڵ��� �ֱ� ���� �ʱ�ȭ �Լ� ���ڿ� �ڵ� ���� �־���
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

		HDC mBackHdc;
		HBITMAP mBackBuffer;

		Vector2 mPlayerPos;				// ��ǥ ������ ����
	};
}
