#pragma once
#include <vector>			// �迭
#include <list>				// ����Ʈ
#include <map>				// Ʈ��
#include <set>				// Ʈ�� 
#include <functional>		// �Լ� ������
#include "framework.h"	// �������� ���
#include <filesystem>	
#include "hyMath.h"
#include <string>
#include <bitset>

//#include <gdiplus.h>
//#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")

namespace hy::enums
{
	enum class eLayerType
	{
		Background,
		Tile,		// �������� Ÿ���� �ٴں��� �ڿ� ���̾ ���� ��
		Floor,
		Player,
		Monster,
		Effect,
		UI,
		End,
	};

	enum class eComponentType	// �ʿ信 ���� ����ϴ� ��ǰ���� ����
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		Rigidbody,
		End,
	};
}