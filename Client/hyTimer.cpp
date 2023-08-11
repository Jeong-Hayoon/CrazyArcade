#include "hyTimer.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyUI.h"
#include "hyObject.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"
#include "hyTransform.h"


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
	}
	void Timer::Update()
	{

		switch (mState)
		{
		case hy::Timer::eState::Zero:
			Zero();
			break;
		case hy::Timer::eState::One:
			One();
			break;
		case hy::Timer::eState::Two:
			Two();
			break;
		case hy::Timer::eState::Three:
			Three();
			break;
		case hy::Timer::eState::Four:
			Four();
			break;
		case hy::Timer::eState::Five:
			Five();
			break;
		case hy::Timer::eState::Six:
			Six();
			break;
		case hy::Timer::eState::Seven:
			Seven();
			break;
		case hy::Timer::eState::Eight:
			Eight();
			break;
		case hy::Timer::eState::Nine:
			Nine();
			break;

		case hy::Timer::eState::End:
			break;
		default:
			break;
		}
	}
	void Timer::Render(HDC hdc)
	{
	}
	void Timer::Zero()
	{
		Texture* Zero_ = Resources::Load<Texture>(L"TimeZero"
			, L"..\\Resources\\Image\\UI\\Timer\\Zero\\Time(0).bmp");

		UI* Zero_ui = object::Instantiate<UI>(eLayerType::UI);
		Transform* Zero_Timertr = this->GetComponent<Transform>();
		Vector2 Zeropos = Zero_Timertr ->GetPosition();
		Zero_ui->GetComponent<Transform>()->SetPosition(Zeropos);
		SpriteRenderer* Zerosr = Zero_ui->AddComponent<SpriteRenderer>();
		Zerosr->SetImage(Zero_);
	}

	void Timer::One()
	{
		Texture* One_ = Resources::Load<Texture>(L"TimeOne"
			, L"..\\Resources\\Image\\UI\\Timer\\One\\Time(1).bmp");

		UI* One_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Onesr = One_ui->GetComponent<SpriteRenderer>();
		Onesr->SetImage(One_);
	}

	void Timer::Two()
	{
		Texture* Two_ = Resources::Load<Texture>(L"TimeTwo"
			, L"..\\Resources\\Image\\UI\\Timer\\Two\\Time(2).bmp");

		UI* Two_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Twosr = Two_ui->GetComponent<SpriteRenderer>();
		Twosr->SetImage(Two_);
	}
	void Timer::Three()
	{
		Texture* Three_ = Resources::Load<Texture>(L"TimeThree"
			, L"..\\Resources\\Image\\UI\\Timer\\Three\\Time(3).bmp");

		UI* Three_ui = object::Instantiate<UI>(eLayerType::UI);

		SpriteRenderer* Threesr = Three_ui->GetComponent<SpriteRenderer>();
		Threesr->SetImage(Three_);
	}
	void Timer::Four()
	{
		Texture* Four_ = Resources::Load<Texture>(L"TimeFour"
			, L"..\\Resources\\Image\\UI\\Timer\\Four\\Time(4).bmp");

		UI* Four_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Foursr = Four_ui->GetComponent<SpriteRenderer>();
		Foursr->SetImage(Four_);
	}
	void Timer::Five()
	{
		Texture* Five_ = Resources::Load<Texture>(L"TimeFive"
			, L"..\\Resources\\Image\\UI\\Timer\\Five\\Time(5).bmp");

		UI* Five_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Fivesr = Five_ui->GetComponent<SpriteRenderer>();
		Fivesr->SetImage(Five_);
	}
	void Timer::Six()
	{
		Texture* Six_ = Resources::Load<Texture>(L"TimeSix"
			, L"..\\Resources\\Image\\UI\\Timer\\Six\\Time(6).bmp");

		UI* Six_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Sixsr = Six_ui->GetComponent<SpriteRenderer>();
		Sixsr->SetImage(Six_);
	}
	void Timer::Seven()
	{
		Texture* Seven_ = Resources::Load<Texture>(L"TimeSeven"
			, L"..\\Resources\\Image\\UI\\Timer\\Seven\\Time(7).bmp");

		UI* Seven_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Sevensr = Seven_ui->GetComponent<SpriteRenderer>();
		Sevensr->SetImage(Seven_);
	}

	void Timer::Eight()
	{
		Texture* Eight_ = Resources::Load<Texture>(L"TimeEight"
			, L"..\\Resources\\Image\\UI\\Timer\\Eight\\Time(8).bmp");

		UI* Eight_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Eightsr = Eight_ui->GetComponent<SpriteRenderer>();
		Eightsr->SetImage(Eight_);
	}
	void Timer::Nine()
	{
		Texture* Nine_ = Resources::Load<Texture>(L"TimeNine"
			, L"..\\Resources\\Image\\UI\\Timer\\Nine\\Time(9).bmp");

		UI* Nine_ui = object::Instantiate<UI>(eLayerType::UI);
		SpriteRenderer* Ninesr = Nine_ui->GetComponent<SpriteRenderer>();
		Ninesr->SetImage(Nine_);
	}

	// 10초마다 갱신
	void Timer::Ten_Seconds()
	{
		static float Ten_Second_time = 0.f;
		Ten_Second_time += Time::DeltaTime();
		if(Ten_Second_time == 10.f)
		{


		}
	}

	// 1초마다 갱신
	void Timer::Seconds()
	{
		static float Seconds = 0.f;
		Seconds += Time::DeltaTime();
		if (Seconds < 11.f)
		{
			if (Seconds == 0.f)
			{
				mState = eState::Zero;
			}

			else if (Seconds == 1.f)
			{
				mState = eState::Nine;
			}

			else if (Seconds == 2.f)
			{
				mState = eState::Eight;
			}

			else if (Seconds == 3.f)
			{
				mState = eState::Seven;
			}

			else if (Seconds == 4.f)
			{
				mState = eState::Six;
			}

			else if (Seconds == 5.f)
			{
				mState = eState::Five;
			}

			else if (Seconds == 6.f)
			{
				mState = eState::Four;
			}

			else if (Seconds == 7.f)
			{
				mState = eState::Three;
			}

			else if (Seconds == 8.f)
			{
				mState = eState::Two;
			}

			else if (Seconds == 9.f)
			{
				mState = eState::One;
			}

			else if (Seconds == 10.f)
			{
				mState = eState::Zero;
				Seconds = 0.f;
			}
		}
	}

	// 1분마다 갱신
	void Timer::Minutes()
	{
		static float Minutes = 0.f;
		Minutes += Time::DeltaTime();
		if (Minutes == 60.f)
		{

		}
	}
}