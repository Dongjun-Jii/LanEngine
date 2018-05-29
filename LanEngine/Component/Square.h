#pragma once
#include "Component.h"

namespace Lan
{
	class Square : public Component
	{
	public:
		Square(DirectX::XMFLOAT2 & size);
		Square(DirectX::XMFLOAT2 && size);
		virtual ~Square();

		void setSize(DirectX::XMFLOAT2 & size);
		void setSize(DirectX::XMFLOAT2 && size);

	protected:
		virtual void onDraw() override;

	private:
		void resizeVertexBuffer();

		DirectX::XMFLOAT2 m_Size;
		ID3D11Buffer * m_VertexBuffer;
		ID3D11Buffer * m_IndexBuffer;
		ID3D11Buffer * m_ConstantBuffer;
	};
}