#pragma once
#include "../Utils/Utils.h"

namespace Lan
{
	class ShaderManager final : public Singleton<ShaderManager>
	{
	public:
		friend Singleton<ShaderManager>;

		void bind();

	private:
		ShaderManager();
		~ShaderManager();

		ID3D11VertexShader* m_VShader;
		ID3D11PixelShader* m_PShader;
		ID3D11InputLayout* m_Layout;

		ID3D11SamplerState* m_SamplerState;
	};
}