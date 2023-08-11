#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class Timer : public GameObject
	{
	public:
		Timer();
		virtual ~Timer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		void Idle();
		void Ten_Seconds();
		void Seconds();
		void Minutes();

	private:
	};
}




