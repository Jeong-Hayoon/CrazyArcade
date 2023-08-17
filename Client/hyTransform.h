#pragma once
#include "hyComponent.h"

namespace hy
{
	using namespace math;

	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize()  override;
		virtual void Update()  override;
		virtual void Render(HDC hdc)  override;

		void SetPosition(Vector2 position) { mPosition = position; }
		Vector2 GetPosition() { return mPosition; }
		void SetRotation(float rotate) { mRotation = rotate; }
		float GetRotation() { return mRotation; }
		void SetScale(Vector2 size) { mScale = size; }


	private:
		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;


	};
}


