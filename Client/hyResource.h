#pragma once
#include "hyEntity.h"

namespace hy
{	// �Ȱ��� �̹����� �ּҰ����� �ؼ� �������Ŵϱ� �̸��� ��θ� �����ؾ� ��
	class Resource : public Entity	// ���������Լ��� �����ϱ� ������ �߻� Ŭ����
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;		// HRESULT bool�� ���� ���� �ڷ���
																// Load�� ���������Լ��� ������ �������̵��� �ؾ���
		std::wstring& GetPath() { return mPath; }
		// �����Ϳ� ���� ������ �ϴµ� �����ʹ� ���� �����ϴϱ� �����ڸ� ���
		// �׳� wstring ���θ� ���� ���縦 2�� �ؼ� �뷮�� ���� ��� �����ϰ� �ּҰ� ��ü�� ���

		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mPath;			// �̸��� Entity�� ��ӹ޾Ƽ� �ʿ� X
	};
}


