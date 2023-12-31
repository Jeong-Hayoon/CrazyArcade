#pragma once
#include <vector>			// 배열
#include <list>				// 리스트
#include <map>				// 트리
#include <set>				// 트리 
#include <functional>		// 함수 포인터
#include "framework.h"	// 윈도우즈 헤더
#include <filesystem>	
#include "hyMath.h"
#include <string>
#include <bitset>
#include <assert.h>

// 사운드 관련
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
	// 타일 사이즈 가로, 세로
	#define TILE_WIDTH 40
	#define TILE_HEIGHT 40

	enum class eLayerType
	{
		Collider,
		Background,
		Tile,		// 나무같은 타일은 바닥보다 뒤에 레이어를 놔야 함
		Floor,
		Bomb,
		Player,
		UseItem,
		Item,
		Monster,
		Boss,
		Effect,
		BossBombflow,
		Bombflow,
		UI,
		End,
	};

	enum class eComponentType	// 필요에 따라 사용하는 부품같은 역할
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