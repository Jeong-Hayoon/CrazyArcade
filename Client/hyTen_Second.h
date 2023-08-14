#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class Ten_Second : public GameObject
	{
	public:

		Ten_Second();
		virtual ~Ten_Second();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:

	};
}




