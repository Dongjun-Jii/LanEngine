#pragma once
#include "../Defines.h"
#include "Component.h"

namespace Lan
{
	class Camera : public Component
	{
	public:
		Camera(Object* parent);
		Camera(Object* parent, float width, float height);
		Camera(Object* parent, fvec2& size);
		Camera(Object* parent, fvec2&& size);
		virtual ~Camera();

		void SetViewSize(fvec2& size);
		void SetViewSize(fvec2&& size);
		const fvec2& GetViewSize() const;

	protected:
		virtual void OnDraw() override;

	private:
		void CreateViewBuffer();
		void UpdateViewBuffer();

		fvec2 m_Size;

		ID3D11Buffer* m_ViewMatrixBuffer;
	};
}