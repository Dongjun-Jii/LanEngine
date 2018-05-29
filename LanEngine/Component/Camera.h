#pragma once
#include "../Defines.h"
#include "Component.h"

namespace Lan
{
	class Camera : public Component
	{
	public:
		Camera();
		Camera(float width, float height);
		Camera(fvec2& size);
		Camera(fvec2&& size);
		virtual ~Camera();

		void setViewSize(fvec2& size);
		void setViewSize(fvec2&& size);
		const fvec2& getViewSize() const;

	protected:
		virtual void onDraw() override;

	private:
		void createViewBuffer();
		void updateViewBuffer();

		fvec2 m_Size;

		ID3D11Buffer* m_ViewMatrixBuffer;
	};
}