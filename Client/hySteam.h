#pragma once
#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class Steam : public GameObject
	{
	public:
	
		enum class eState
		{
			Make,
			Extinct,
			End,
		};

		Steam();
		virtual ~Steam();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		void Make();
		void Extinct();


	private:
		eState mState;
	};
}



