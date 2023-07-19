#pragma once
#include "CommonInclude.h"

// enum : ���ڸ� ���ڷ� �ٲ� �� �ִ� ����
// static : ��������ó�� �����ϵ� Ŭ���� ���ο� �����ϰ� ���� ���(��������) - ���������� ���� ����(������)
//				private�� ������ �� ���� / ��ü�� ���� ������ �ʾƵ� ����� �� ����
// bool : 0 �Ǵ� 1�� �����ϱ� ���� ����(1byte)
//				true(1) / false(0)
namespace hy
{
	enum class eKeyCode			// Ű���� Ű�� enum���� ��Ī
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Up, Down, Left, Right,
		MouseLeft, MouseRight, MouseWheel,
		End,					// End�� �迭�� ũ�⸦ �ٷ궧 26�� ���ϰ� ����� �� �ֵ���
	};
	enum class eKeyState		// Ű�� ����
	{
		Down,			// 0
		Up,				// 1
		Pressed,		// 2
		None,			// 3
	};

	class Input
	{
	public:
		struct Key			// Ű���� Ű �ϳ��� �� ����ü ������ �ϳ��� �� ������ �ִ� ��
		{
			eKeyCode code;					// ���� Ű����
			eKeyState state;				// �� �����ӿ��� �� Ű�� � ��������
			bool bPressed;					// ���� �����ӿ��� Ű�� �����־�����
		};

		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code)					// inline : ����ȭ �ɼ�, ���� ���Ǵ� �͵��� �ζ��� ����ϴ°� ����
		{																							// _forceinline : inline�� ������(�Ǵܾ���)
			return mKeys[(int)code].state == eKeyState::Down;				// inline�� ��������� ��� ����
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Up;
		}
		__forceinline static bool GetKey(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Pressed;				// ������ true ��ȯ, �ٸ��� false ��ȯ
		}
		 
	private:
		static std::vector<Key> mKeys;
	};

	// vector�� ������ <�ڷ���>�� �����
}

