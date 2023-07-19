#pragma once
#include "CommonInclude.h"

// enum : 숫자를 문자로 바꿀 수 있는 문법
// static : 전역변수처럼 동작하되 클래스 내부에 선언하고 싶은 경우(정적변수) - 전역변수와 같은 영역(데이터)
//				private를 지정할 수 있음 / 객체를 따로 만들지 않아도 사용할 수 있음
// bool : 0 또는 1을 저장하기 위한 변수(1byte)
//				true(1) / false(0)
namespace hy
{
	enum class eKeyCode			// 키보드 키를 enum으로 매칭
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Up, Down, Left, Right,
		MouseLeft, MouseRight, MouseWheel,
		End,					// End는 배열의 크기를 다룰때 26을 편하게 사용할 수 있도록
	};
	enum class eKeyState		// 키의 상태
	{
		Down,			// 0
		Up,				// 1
		Pressed,		// 2
		None,			// 3
	};

	class Input
	{
	public:
		struct Key			// 키보드 키 하나당 이 구조체 정보를 하나씩 다 가지고 있는 것
		{
			eKeyCode code;					// 무슨 키인지
			eKeyState state;				// 현 프레임에서 내 키가 어떤 상태인지
			bool bPressed;					// 이전 프레임에서 키가 눌려있었는지
		};

		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code)					// inline : 최적화 옵션, 자주 사용되는 것들은 인라인 사용하는게 좋음
		{																							// _forceinline : inline을 무조건(판단없이)
			return mKeys[(int)code].state == eKeyState::Down;				// inline은 헤더에서만 사용 가능
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Up;
		}
		__forceinline static bool GetKey(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Pressed;				// 같으면 true 반환, 다르면 false 반환
		}
		 
	private:
		static std::vector<Key> mKeys;
	};

	// vector는 무조건 <자료형>을 써야함
}

