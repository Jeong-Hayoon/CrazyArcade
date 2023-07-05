#pragma once
#include <vector>			// �迭
#include <list>				// ����Ʈ
#include <map>				// Ʈ��
#include <set>				// Ʈ�� 
#include <functional>		// �Լ� ������
#include "framework.h"	// �������� ���
#include "wzMath.h"
#include <string>


namespace wz::enums
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