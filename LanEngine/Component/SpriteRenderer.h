#pragma once
#include "Component.h"

namespace Lan
{
	class Texture;

	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer(Object* parent);
		SpriteRenderer(Object* parent, tstring textureName);
		~SpriteRenderer();

		void SetTexture(tstring name);
		Texture* GetTexture() const;

	protected:
		virtual void OnDraw() override;

	private:
		void CreateTexCoordBuffer();

		Texture * m_Sprite;
		ID3D11Buffer* m_TexCoordBuffer;
	};
}