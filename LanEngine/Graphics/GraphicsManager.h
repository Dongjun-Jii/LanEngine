#pragma once
#include "../Utils/Utils.h"
#pragma comment(lib, "d3d11.lib")

namespace Lan
{
	class GraphicsManager final : public Singleton<GraphicsManager>
	{
	public:
		friend Singleton <GraphicsManager>;

		void Initialize(HWND windowHandle, DirectX::XMINT2 resolution, bool isFullScreen);

		ID3D11Device * GetDevice();
		ID3D11DeviceContext * GetDeviceContext();

		void BeginDraw();
		void EndDraw();
	private:
		GraphicsManager();
		~GraphicsManager();

		IDXGISwapChain * m_SwapChain;
		ID3D11Device * m_Device;
		ID3D11DeviceContext * m_DeviceContext;
		D3D_FEATURE_LEVEL m_FeatureLevel;
		ID3D11RenderTargetView * m_RenderTargetView;
		ID3D11Texture2D * m_DepthStencilBuffer;
		ID3D11DepthStencilView * m_DepthStencilView;
	};
}