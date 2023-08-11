#include "hyTimer.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyUI.h"
#include "hyObject.h"

namespace hy
{
	Timer::Timer()
	{
	}
	Timer::~Timer()
	{
	}
	void Timer::Initialize()
	{
		Texture* Zero = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Zero\\Time(0).bmp");

		Texture* One = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\One\\Time(1).bmp");

		Texture* Two = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Two\\Time(2).bmp");

		Texture* Three = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Three\\Time(3).bmp");

		Texture* Four = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Four\\Time(4).bmp");

		Texture* Five = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Five\\Time(5).bmp");

		Texture* Six = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Six\\Time(6).bmp");

		Texture* Seven = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Seven\\Time(7).bmp");

		Texture* Eight = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Eight\\Time(8).bmp");

		Texture* Nine = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\UI \\Timer\\Nine\\Time(9).bmp");
	}
	void Timer::Update()
	{
	}
	void Timer::Render(HDC hdc)
	{
	}
	void Timer::Idle()
	{
	}
	void Timer::Ten_Seconds()
	{
	}
	void Timer::Seconds()
	{
	}
	void Timer::Minutes()
	{
	}
}