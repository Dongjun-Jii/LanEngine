#include "Defines.h"
#include "Transform.h"

namespace Lan
{
	Transform::Transform() :
		position({ 0, 0 }),
		size({ 1, 1 }),
		angle(0),
		depth(0)
	{

	}

	void Transform::move(const DirectX::XMFLOAT2& offset)
	{
		position.x += offset.x;
		position.y += offset.y;
	}

	void Transform::move(const DirectX::XMFLOAT2&& offset)
	{
		position.x += offset.x;
		position.y += offset.y;
	}

	void Transform::stretch(const DirectX::XMFLOAT2& offset)
	{
		size.x *= offset.x;
		size.y *= offset.y;
	}

	void Transform::stretch(const DirectX::XMFLOAT2&& offset)
	{
		size.x *= offset.x;
		size.y *= offset.y;
	}
}