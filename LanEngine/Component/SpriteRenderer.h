#pragma once
#include "Component.h"

namespace Lan
{
	class Texture;

	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		SpriteRenderer(tstring textureName);
		~SpriteRenderer();

		void setTexture(tstring name);
		Texture* getTexture() const;

	protected:
		virtual void onDraw() override;

	private:
		Texture * m_Sprite;
		ID3D11Buffer* m_TexCoordBuffer;
	};
}