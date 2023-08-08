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
#include <assert.h>

// ���� ����
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

//#include <gdiplus.h>
//#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")

namespace hy::enums
{
	// Ÿ�� ������ ����, ����
	#define TILE_WIDTH 40
	#define TILE_HEIGHT 40

	enum class eLayerType
	{
		Collider,
		Background,
		Tile,		// �������� Ÿ���� �ٴں��� �ڿ� ���̾ ���� ��
		Floor,
		Player,
		UseItem,
		Item,
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