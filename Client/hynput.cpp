#include "hyInput.h"

// UINT : unsigned int(양수)

namespace hy
{
	std::vector<Input::Key> Input::mKeys = {};					// static 변수는 외부에서 초기화를 반드시 해줘야 함

	int ASCII[(int)eKeyCode::End] =								// 아스키코드를 배열안에 넣어 놓음(enum이랑 아스키코드 매칭)
	{																			// (int)eKeyCode::End -> End가 26인데 eKeyCode::End가 클래스라 int로 강제 캐스팅
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,						// 상하좌우
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,						// 마우스 버튼, 휠
		VK_SPACE
	};

	void Input::Initialize()
	{
		for (int  i = 0; i < (int)eKeyCode::End; i++)
		{
			Key key = {};
			key.code = (eKeyCode)i;					// 0~25까지 넣어줌
			key.state = eKeyState::None;			// 초기화이므로 None 상태
			key.bPressed = false;					// 초기화이므로 false 상태

			mKeys.push_back(key);					// 배열에 키 정보 넣기
		}
	}

	void Input::Update()							// 키가 눌린거 확인
	{
		for (int  i = 0; i < (int)eKeyCode::End; i++)
		{
			// 해당키가 눌려졌다.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// 이전 프레임에도 눌려져 있었다.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

				mKeys[i].bPressed = true;			// 이전에 눌렀다
			}
			else // 해당키가 안눌려져 있다.
			{
				// 이전프레임에 눌려져 있었다.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Up;
				else
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;			// 이전에 안눌렀다
			}
		}
	}
}