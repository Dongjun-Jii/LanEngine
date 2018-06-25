#include "Defines.h"
#include "Transform.h"
#include "../Object/Object.h"

using namespace DirectX;

namespace Lan
{
	Transform::Transform(Object* parent) :
		Component(parent),
		m_LocalPosition(fvec3(0, 0, 0)),
		m_LocalAngle(0),
		m_Scale({ 1, 1 })
	{
		BalanceTransform(Space::Local);
	}

	void Transform::Translate(fvec3& offset, Space space)
	{
		Translate(std::move(offset), space);
	}

	void Transform::Translate(fvec3&& offset, Space space)
	{
		if (space == Space::Local)
		{
			vector dst = XMLoadFloat3(&m_LocalPosition);
			vector src = XMLoadFloat3(&offset);
			dst = XMVectorAdd(dst, src);
			XMStoreFloat3(&m_LocalPosition, dst);
		}
		else if (space == Space::World)
		{
			vector dst = XMLoadFloat3(&m_Position);
			vector src = XMLoadFloat3(&offset);
			dst = XMVectorAdd(dst, src);
			XMStoreFloat3(&m_Position, dst);
		}

		BalanceTransform(space);
	}

	void Transform::SetTranslation(fvec3& position, Space space)
	{
		SetTranslation(std::move(position), space);
	}

	void Transform::SetTranslation(fvec3&& position, Space space)
	{
		if (space == Space::Local)
		{
			m_LocalPosition = position;
		}
		else if (space == Space::World)
		{
			m_Position = position;
		}

		BalanceTransform(space);
	}

	const fvec3& Transform::GetTranslate() const
	{
		return m_Position;
	}

	const fvec3& Transform::GetLocalTranslate() const
	{
		return m_LocalPosition;
	}

	void Transform::Rotate(float32 angle)
	{
		m_Angle += angle;
		BalanceTransform(Space::World);
	}

	void Transform::SetRotation(float32 angle, Space space)
	{
		if (space == Space::Local)
		{
			m_LocalAngle = angle;
		}
		else if (space == Space::World)
		{
			m_Angle = angle;
		}

		BalanceTransform(space);
	}

	float32 Transform::GetRotate() const
	{
		return m_Angle;
	}

	float32 Transform::GetLocalRotate() const
	{
		return m_LocalAngle;
	}

	void Transform::Scale(fvec2& offset)
	{
		Scale(std::move(offset));
	}

	void Transform::Scale(fvec2&& offset)
	{
		vector dst = XMLoadFloat2(&m_Scale);
		vector src = XMLoadFloat2(&offset);
		dst = XMVectorMultiply(dst, src);
		XMStoreFloat2(&m_Scale, dst);
	}

	void Transform::SetScale(fvec2& offset)
	{
		SetScale(std::move(offset));
	}

	void Transform::SetScale(fvec2&& offset)
	{
		m_Scale = offset;
	}

	const fvec2& Transform::GetScale() const
	{
		return m_Scale;
	}

	matrix Transform::GetWorldMatrix() const
	{
		matrix translate = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		matrix rotate = XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), m_Angle);
		matrix scale = XMMatrixScaling(m_Scale.x, m_Scale.y, 1);

		matrix world = scale * rotate * translate;
		
		return world;
	}

	void Transform::BalanceTransform(Space space)
	{
		BalanceRotation(space);
		BalanceTranslation(space);

		for (auto obj : GetParent().GetChildren())
		{
			obj->GetTransform().BalanceTransform(Space::Local);
		}
	}

	void Transform::BalanceTranslation(Space space)
	{
		if (space == Space::Local)
		{
			if (GetParent().GetParent())
			{
				vector lpos = XMLoadFloat3(&m_LocalPosition);
				vector pos = XMVector3Transform(lpos, GetParent().GetParent()->GetTransform().GetWorldMatrix());
				XMStoreFloat3(&m_Position, pos);
			}
			else
			{
				m_Position = m_LocalPosition;
			}
		}
		else
		{
			if (GetParent().GetParent())
			{
				vector pos = XMLoadFloat3(&m_LocalPosition);
				vector lpos = XMVector3Transform(pos, 
					XMMatrixTranspose(GetParent().GetParent()->GetTransform().GetWorldMatrix()));
				XMStoreFloat3(&m_LocalPosition, lpos);
			}
			else
			{
				m_LocalPosition = m_Position;
			}
		}
	}

	void Transform::BalanceRotation(Space space)
	{
		if (space == Space::Local)
		{
			if (GetParent().GetParent())
			{
				m_Angle = m_LocalAngle + GetParent().GetParent()->GetTransform().GetRotate();
			}
			else
			{
				m_Angle = m_LocalAngle;
			}
		}
		else
		{
			if (GetParent().GetParent())
			{
				m_LocalAngle = GetParent().GetParent()->GetTransform().GetRotate() - m_Angle;
			}
			else
			{
				m_LocalAngle = m_Angle;
			}
		}
	}
}