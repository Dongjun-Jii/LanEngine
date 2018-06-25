#include "Defines.h"
#include "Camera.h"
#include "../Graphics/GraphicsManager.h"
#include "../Object/Object.h"

namespace Lan
{
	Camera::Camera(Object* parent) :
		Camera(parent, fvec2(2, 2))
	{

	}

	Camera::Camera(Object* parent, float width, float height) :
		Camera(parent, fvec2(width, height))
	{

	}

	Camera::Camera(Object* parent, fvec2& size) :
		Camera(parent, std::move(size))
	{

	}

	Camera::Camera(Object* parent, fvec2&& size) :
		Component(parent),
		m_Size(size)
	{
		CreateViewBuffer();
	}

	Camera::~Camera()
	{

	}

	void Camera::SetViewSize(fvec2& size)
	{
		m_Size = size;
	}

	void Camera::SetViewSize(fvec2&& size)
	{
		m_Size = size;
	}

	const fvec2& Camera::GetViewSize() const
	{
		return m_Size;
	}

	void Camera::OnDraw()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::GetInstance().GetDeviceContext();

		UpdateViewBuffer();

		deviceContext->VSSetConstantBuffers(1, 1, &m_ViewMatrixBuffer);
	}

	void Camera::CreateViewBuffer()
	{
		ID3D11Device* device = GraphicsManager::GetInstance().GetDevice();
		HRESULT result;

		D3D11_BUFFER_DESC vbd;
		vbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		vbd.ByteWidth = sizeof(fmat44);
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		vbd.Usage = D3D11_USAGE_DYNAMIC;

		result = device->CreateBuffer(&vbd, nullptr, &m_ViewMatrixBuffer);
		if (FAILED(result))
		{
			throw std::runtime_error("Create Camera Buffer Failed");
		}
	}

	void Camera::UpdateViewBuffer()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::GetInstance().GetDeviceContext();

		fvec3 pos = GetParent().GetTransform().GetTranslate();
		fvec4 eye = { 0, 0, 1, 0 };
		fvec4 up = { DirectX::XMScalarSin(GetParent().GetTransform().GetRotate()),
			DirectX::XMScalarCos(GetParent().GetTransform().GetRotate()), 0, 0 };

		matrix vMat = DirectX::XMMatrixLookToLH(
			DirectX::XMLoadFloat3(&pos),
			DirectX::XMLoadFloat4(&eye),
			DirectX::XMLoadFloat4(&up));

		matrix oMat = DirectX::XMMatrixOrthographicLH(m_Size.x, m_Size.y, 0, 100);

		D3D11_MAPPED_SUBRESOURCE vmr;
		deviceContext->Map(m_ViewMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vmr);
		
		DirectX::XMStoreFloat4x4(static_cast<fmat44 *>(vmr.pData), vMat * oMat);

		deviceContext->Unmap(m_ViewMatrixBuffer, 0);
	}
}