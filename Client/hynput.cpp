#include "hyInput.h"

// UINT : unsigned int(���)

namespace hy
{
	std::vector<Input::Key> Input::mKeys = {};					// static ������ �ܺο��� �ʱ�ȭ�� �ݵ�� ����� ��

	int ASCII[(int)eKeyCode::End] =								// �ƽ�Ű�ڵ带 �迭�ȿ� �־� ����(enum�̶� �ƽ�Ű�ڵ� ��Ī)
	{																			// (int)eKeyCode::End -> End�� 26�ε� eKeyCode::End�� Ŭ������ int�� ���� ĳ����
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,						// �����¿�
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,						// ���콺 ��ư, ��
		VK_SPACE
	};

	void Input::Initialize()
	{
		for (int  i = 0; i < (int)eKeyCode::End; i++)
		{
			Key key = {};
			key.code = (eKeyCode)i;					// 0~25���� �־���
			key.state = eKeyState::None;			// �ʱ�ȭ�̹Ƿ� None ����
			key.bPressed = false;					// �ʱ�ȭ�̹Ƿ� false ����

			mKeys.push_back(key);					// �迭�� Ű ���� �ֱ�
		}
	}

	void Input::Update()							// Ű�� ������ Ȯ��
	{
		for (int  i = 0; i < (int)eKeyCode::End; i++)
		{
			// �ش�Ű�� ��������.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ������ �־���.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

				mKeys[i].bPressed = true;			// ������ ������
			}
			else // �ش�Ű�� �ȴ����� �ִ�.
			{
				// ���������ӿ� ������ �־���.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Up;
				else
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;			// ������ �ȴ�����
			}
		}
	}
}