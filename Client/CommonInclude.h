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

//#include <gdiplus.h>
//#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")

namespace hy::enums
{
	enum class eLayerType
	{
		Background,
		Tile,		// 나무같은 타일은 바닥보다 뒤에 레이어를 놔야 함
		Floor,
		Player,
		Monster,
		Effect,
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