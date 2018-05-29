#pragma once
#include "Component.h"
#include <DirectXMath.h>

namespace Lan
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform() = default;

		void move(const DirectX::XMFLOAT2& offset);
		void move(const DirectX::XMFLOAT2&& offset);

		void stretch(const DirectX::XMFLOAT2& offset);
		void stretch(const DirectX::XMFLOAT2&& offset);

		DirectX::XMFLOAT2 position;
		DirectX::XMFLOAT2 size;

		int32 depth;
		float32 angle;
	};
}