#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class Second : public GameObject
	{
	public:

		/*enum class eState
		{
			Zero,
			One,
			Two,
			Three,
			Four,
			Five,
			Six,
			Seven,
			Eight,
			Nine,
			End,
		};*/

		Second();
		virtual ~Second();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		//void Zero();
		//void One();
		//void Two();
		//void Three();
		//void Four();
		//void Five();
		//void Six();
		//void Seven();
		//void Eight();
		//void Nine();

		/*void Ten_Seconds();
		void Seconds();
		void Minutes();*/

	private:
		//eState mState;

	};
}




