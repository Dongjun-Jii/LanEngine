#pragma once
#include "Resource.h"
#include "../Defines.h"

namespace Lan
{
	class Texture : public Resource
	{
	public:
		Texture(void * buffer, tsize len, tstring path, tstring extension);
		virtual ~Texture();

		int32 getWidth() const;
		int32 getHeight() const;
		int32 getChannel() const;

		ID3D11Texture2D * getTextureBuffer() const;
		ID3D11ShaderResourceView* getTextureView() const;

	private:
		int32 m_Width;
		int32 m_Height;
		int32 m_Channel;

		ID3D11Texture2D* m_Buffer;
		ID3D11ShaderResourceView* m_View;
	};
}