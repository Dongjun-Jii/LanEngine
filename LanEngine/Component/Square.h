#pragma once
#include "Component.h"

namespace Lan
{
	class Square : public Component
	{
	public:
		Square(Object* parent, DirectX::XMFLOAT2 & size);
		Square(Object* parent, DirectX::XMFLOAT2 && size);
		virtual ~Square();

		void SetSize(DirectX::XMFLOAT2 & size);
		void SetSize(DirectX::XMFLOAT2 && size);

	protected:
		virtual void OnDraw() override;

	private:
		void ResizeVertexBuffer();

		DirectX::XMFLOAT2 m_Size;
		ID3D11Buffer * m_VertexBuffer;
		ID3D11Buffer * m_IndexBuffer;
		ID3D11Buffer * m_ConstantBuffer;
	};
}