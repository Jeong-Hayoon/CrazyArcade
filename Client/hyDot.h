#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class Timer_Dot : public GameObject
	{
	public:

		Timer_Dot();
		virtual ~Timer_Dot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:

	};
}




