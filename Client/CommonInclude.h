#pragma once
#include <vector>			// �迭
#include <list>				// ����Ʈ
#include <map>				// Ʈ��
#include <set>				// Ʈ�� 
#include <functional>		// �Լ� ������
#include "framework.h"	// �������� ���
#include "hyMath.h"
#include <string>
//#include <gdiplus.h>
//#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")


namespace hy::enums
{
	enum class eLayerType
	{
		Background,
		Player,
		Monster,
		Effect,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		End,
	};
}