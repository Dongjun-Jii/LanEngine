#include "Defines.h"
#include "ShaderManager.h"
#include "GraphicsManager.h"

namespace Lan
{
	ShaderManager::ShaderManager():
		m_VShader(nullptr),
		m_PShader(nullptr),
		m_Layout(nullptr)
	{
		ID3D11Device * device = GraphicsManager::GetInstance().GetDevice();
		HRESULT result;
		
		int8* vsBuffer = nullptr;
		int8* psBuffer = nullptr;
		int32 vsLen = 0;
		int32 psLen = 0;
		
		try
		{
			//버텍스, 픽셀 셰이더 오브젝트 읽기
			std::ifstream vStream("VertexShader.cso", std::ios_base::binary);
			vStream.seekg(0, std::ios_base::end);
			vsLen = static_cast<int32>(vStream.tellg());
			vStream.seekg(0, std::ios_base::beg);

			vsBuffer = new int8[vsLen];

			vStream.read(reinterpret_cast<char *>(vsBuffer), vsLen);
			vStream.close();

			std::ifstream pStream("PixelShader.cso", std::ios_base::binary);
			pStream.seekg(0, std::ios_base::end);
			psLen = static_cast<int32>(pStream.tellg());
			pStream.seekg(0, std::ios_base::beg);

			psBuffer = new int8[psLen];

			
			pStream.read(reinterpret_cast<char *>(psBuffer), psLen);
			pStream.close();
		}
		catch (const std::ios_base::failure& e)
		{
			LOG(LogLevel::Error, e.what());
		}
		

		

		//버텍스 픽셀 셰이더 생성
		result = device->CreateVertexShader(vsBuffer, vsLen, nullptr, &m_VShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create vertex Shader Failed");
		}

		result = device->CreatePixelShader(psBuffer, psLen, nullptr, &m_PShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create Pixel Shader Failed");
		}

		D3D11_INPUT_ELEMENT_DESC ied[2];
		ied[0].AlignedByteOffset = 0;
		ied[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		ied[0].InputSlot = 0;
		ied[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ied[0].InstanceDataStepRate = 0;
		ied[0].SemanticIndex = 0;
		ied[0].SemanticName = "POSITION";

		ied[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		ied[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		ied[1].InputSlot = 1;
		ied[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ied[1].InstanceDataStepRate = 0;
		ied[1].SemanticIndex = 0;
		ied[1].SemanticName = "TEXCOORD";

		result = device->CreateInputLayout(ied, 2, vsBuffer, vsLen, &m_Layout);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create Input Layout Failed");
		}

		delete[] vsBuffer;
		delete[] psBuffer;

		this->Bind();

		D3D11_SAMPLER_DESC ssd;
		ssd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		ssd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		ssd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		ssd.BorderColor[0] = 1.0f;
		ssd.BorderColor[1] = 1.0f;
		ssd.BorderColor[2] = 1.0f;
		ssd.BorderColor[3] = 1.0f;
		ssd.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
		ssd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		ssd.MaxAnisotropy = 1;
		ssd.MaxLOD = D3D11_FLOAT32_MAX;
		ssd.MinLOD = 0;
		ssd.MipLODBias = 0;

		device->CreateSamplerState(&ssd, &m_SamplerState);

	}

	ShaderManager::~ShaderManager()
	{
		if (m_Layout)
		{
			m_Layout->Release();
			m_Layout = nullptr;
		}
		if (m_VShader)
		{
			m_VShader->Release();
			m_VShader = nullptr;
		}
		if (m_PShader)
		{
			m_PShader->Release();
			m_PShader = nullptr;
		}
	}

	void ShaderManager::Bind()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::GetInstance().GetDeviceContext();

		deviceContext->VSSetShader(m_VShader, 0, 0);
		deviceContext->PSSetShader(m_PShader, 0, 0);
		deviceContext->IASetInputLayout(m_Layout);

		deviceContext->PSSetSamplers(0, 1, &m_SamplerState);
	}
}