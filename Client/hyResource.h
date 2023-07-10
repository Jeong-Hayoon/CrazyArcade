#pragma once
#include "hyEntity.h"

namespace hy
{	// 똑같은 이미지를 주소값으로 해서 나눠쓸거니까 이름과 경로를 저장해야 함
	class Resource : public Entity	// 순수가상함수가 존재하기 때문에 추상 클래스
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;		// HRESULT bool과 거의 같은 자료형
																// Load는 순수가상함수라서 무조건 오버라이딩을 해야함
		std::wstring& GetPath() { return mPath; }
		// 포인터와 같은 역할을 하는데 포인터는 쓰기 불편하니까 참조자를 사용
		// 그냥 wstring 으로만 쓰면 복사를 2번 해서 용량을 많이 잡아 먹으니가 주소값 자체를 사용

		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mPath;			// 이름은 Entity를 상속받아서 필요 X
	};
}


