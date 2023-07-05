#pragma once
#include <vector>			// 배열
#include <list>				// 리스트
#include <map>				// 트리
#include <set>				// 트리 
#include <functional>		// 함수 포인터
#include "framework.h"	// 윈도우즈 헤더
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