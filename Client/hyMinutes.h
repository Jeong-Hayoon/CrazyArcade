#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class Minutes : public GameObject
	{
	public:

		Minutes();
		virtual ~Minutes();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:

	};
}




