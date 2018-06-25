#pragma once
#include "../Utils/Utils.h"
#include "../Input/Input.h"

namespace Lan
{
	class LanEngine;

	class Window final : public Singleton<Window>
	{
	public:
		friend Singleton<Window>;
		friend LanEngine;

		const HWND& GetHandle() const;

		void Update();

		bool ShouldClose() const;

		bool IsActive() const;

		bool SetWindowName(tstring windowName) const;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		Window();
		~Window();

		void Initialize(HINSTANCE instanceHandle, ivec2 size);


		void SetActive(bool active);

		HWND m_WindowHandle;

		int32 m_ConsoleHandle;

		bool m_IsInitialized;
		bool m_ShouldClose;
		bool m_IsActive;
		bool m_HasConsole;
	};
}
