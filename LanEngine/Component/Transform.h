#pragma once
#include "Component.h"
#include <DirectXMath.h>

namespace Lan
{
	enum class Space
	{
		World,
		Local
	};

	class Transform : public Component
	{
	public:
		Transform(Object* parent);
		~Transform() = default;

		void Translate(fvec3& offset, Space space = Space::Local);
		void Translate(fvec3&& offset, Space space = Space::Local);
		void SetTranslation(fvec3& position, Space space = Space::Local);
		void SetTranslation(fvec3&& position, Space space = Space::Local);
		const fvec3& GetTranslate() const;
		const fvec3& GetLocalTranslate() const;

		void Rotate(float32 angle);
		void SetRotation(float32 angle, Space space = Space::Local);
		float32 GetRotate() const;
		float32 GetLocalRotate() const;

		void Scale(fvec2& offset);
		void Scale(fvec2&& offset);
		void SetScale(fvec2& offset);
		void SetScale(fvec2&& offset);
		const fvec2& GetScale() const;

		matrix GetWorldMatrix() const;

		void BalanceTransform(Space space);

	private:
		void BalanceTranslation(Space space);
		void BalanceRotation(Space space);

		fvec3 m_Position;
		fvec3 m_LocalPosition;
		
		fvec2 m_Scale;
		
		float32 m_Angle;
		float32 m_LocalAngle;
	};
}