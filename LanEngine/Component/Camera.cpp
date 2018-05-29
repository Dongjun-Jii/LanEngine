#include "Defines.h"
#include "Camera.h"
#include "../Graphics/GraphicsManager.h"
#include "../Object/Object.h"

namespace Lan
{
	Camera::Camera() : 
		Camera(fvec2(2, 2))
	{

	}

	Camera::Camera(float width, float height) :
		Camera(fvec2(width, height))
	{

	}

	Camera::Camera(fvec2& size) :
		Camera(std::move(size))
	{

	}

	Camera::Camera(fvec2&& size) :
		m_Size(size)
	{
		createViewBuffer();
	}

	Camera::~Camera()
	{

	}

	void Camera::setViewSize(fvec2& size)
	{
		m_Size = size;
	}

	void Camera::setViewSize(fvec2&& size)
	{
		m_Size = size;
	}

	const fvec2& Camera::getViewSize() const
	{
		return m_Size;
	}

	void Camera::onDraw()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::getInstance().getDeviceContext();

		updateViewBuffer();

		deviceContext->VSSetConstantBuffers(1, 1, &m_ViewMatrixBuffer);
	}

	void Camera::createViewBuffer()
	{
		ID3D11Device* device = GraphicsManager::getInstance().getDevice();
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

	void Camera::updateViewBuffer()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::getInstance().getDeviceContext();

		fvec4 pos = { getParent().getTransform().position.x,
			getParent().getTransform().position.y,
			0, 1 };
		fvec4 eye = { 0, 0, 1, 0 };
		fvec4 up = { DirectX::XMScalarSin(getParent().getTransform().angle),
			DirectX::XMScalarCos(getParent().getTransform().angle), 0, 0 };

		matrix vMat = DirectX::XMMatrixLookToLH(
			DirectX::XMLoadFloat4(&pos),
			DirectX::XMLoadFloat4(&eye),
			DirectX::XMLoadFloat4(&up));

		matrix oMat = DirectX::XMMatrixOrthographicLH(m_Size.x, m_Size.y, 0, 100);

		D3D11_MAPPED_SUBRESOURCE vmr;
		deviceContext->Map(m_ViewMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vmr);
		
		DirectX::XMStoreFloat4x4(static_cast<fmat44 *>(vmr.pData), vMat * oMat);

		deviceContext->Unmap(m_ViewMatrixBuffer, 0);
	}
}