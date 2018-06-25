#include "Defines.h"
#include "SpriteRenderer.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Graphics/GraphicsManager.h"

namespace Lan
{
	SpriteRenderer::SpriteRenderer(Object* parent) :
		Component(parent),
		m_Sprite(nullptr),
		m_TexCoordBuffer(nullptr)
	{
		CreateTexCoordBuffer();
	}

	SpriteRenderer::SpriteRenderer(Object* parent, tstring textureName) :
		Component(parent),
		m_Sprite(dynamic_cast<Texture *>(ResourceManager::GetInstance().GetResource(textureName)))
	{
		CreateTexCoordBuffer();
	}

	void SpriteRenderer::CreateTexCoordBuffer()
	{
		ID3D11Device* device = GraphicsManager::GetInstance().GetDevice();
		HRESULT result;

		fvec2 vertices[4] =
		{
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};

		D3D11_BUFFER_DESC vbd;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.ByteWidth = sizeof(fvec2) * 4;
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		vbd.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA vrd;
		vrd.pSysMem = vertices;
		vrd.SysMemPitch = 0;
		vrd.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&vbd, &vrd, &m_TexCoordBuffer);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create TexCoordBuffer Error");
		}
	}

	SpriteRenderer::~SpriteRenderer()
	{
		if (m_TexCoordBuffer)
		{
			m_TexCoordBuffer->Release();
			m_TexCoordBuffer = nullptr;
		}
	}

	void SpriteRenderer::OnDraw()
	{
		ID3D11DeviceContext* deviceContext = GraphicsManager::GetInstance().GetDeviceContext();

		UINT stride = sizeof(fvec2);
		UINT offset = 0;

		if (m_Sprite)
		{
			ID3D11ShaderResourceView* tex = m_Sprite->GetTextureView();
			deviceContext->PSSetShaderResources(0, 1, &tex);
		}

		deviceContext->IASetVertexBuffers(1, 1, &m_TexCoordBuffer, &stride, &offset);
	}

	void SpriteRenderer::SetTexture(tstring name)
	{
		ResourceManager::GetInstance().GetResource(name);
	}

	Texture* SpriteRenderer::GetTexture() const
	{
		return m_Sprite;
	}
}