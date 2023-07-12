#pragma once
#include "CommonInclude.h" 


// ������� ����, �Լ��� ����θ� �ۼ�(������ ��쿡�� ������� ����, ���� ������ ��쿡�� cpp�ʿ� ����)

namespace hy						// namespace�� �ٸ��� Ŭ���� �̸��� ���Ƶ� ����� �� ����
{
	using namespace math;
	class Application				// ���ο��� ������ �ڵ��� Ŭ������ �����ؼ� ����(������ ��ü�� ������ ��� �ִ� Ŭ����)
	{
	public:							// �Լ� ���� �� ��Ŭ�� - ���� �۾� �� �����͸� - ���� ���� �����
		Application();
		~Application();

		void Initialize(HWND hwnd);		// ��������� �ڵ��� �ֱ� ���� �ʱ�ȭ �Լ� ���ڿ� �ڵ� ���� �־���
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;						
		UINT mHeight;

		HDC mBackHdc;							// ���ο� DC
		HBITMAP mBackBuffer;				// ���ο� ȭ��(��ȭ��)
		
		// Vector2 mPlayerPos;				// ��ǥ ������ ����
	};
	// �ܻ� ����� : �׸��� ���� rectangle �Ͼ� �簢������ ������ ��
	// ���� ���۸� �˰��� : ȭ���� �ΰ��� ����Ͽ� ���� ������ �ʴ� ȭ�鿡 �׸��� �׸��� 
	// ȭ�� ��Ŀ���� �ٸ� ������ ����Ͽ� �����Ÿ��� �����(���۶�� ���� �޸� ������ �ǹ�)
}
