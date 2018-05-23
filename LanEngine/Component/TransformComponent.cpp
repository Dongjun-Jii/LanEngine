#include "Defines.h"
#include "TransformComponent.h"

namespace Lan
{
	TransformComponent::TransformComponent() :
		position({ 0, 0 }),
		size({ 1, 1 }),
		angle(0),
		depth(0)
	{

	}

	void TransformComponent::move(const DirectX::XMFLOAT2& offset)
	{
		position.x += offset.x;
		position.y += offset.y;
	}

	void TransformComponent::move(const DirectX::XMFLOAT2&& offset)
	{
		position.x += offset.x;
		position.y += offset.y;
	}

	void TransformComponent::stretch(const DirectX::XMFLOAT2& offset)
	{
		size.x *= offset.x;
		size.y *= offset.y;
	}

	void TransformComponent::stretch(const DirectX::XMFLOAT2&& offset)
	{
		size.x *= offset.x;
		size.y *= offset.y;
	}
}