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

		const HWND& getHandle() const;

		void peekMessage();

		bool shouldClose() const;

		bool isActive() const;

//		bool isFullScreen() const;
//		bool canGoFullScreen() const;
//		void setFullScreen(HWND hWnd, bool fullscreen);
//		void toggleFullScreen(HWND hWnd);

		bool setWindowName(tstring windowName) const;	//윈도우 이름 바꾸기

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		Window();
		~Window();

		void initialize(HINSTANCE instanceHandle, ivec2 size);


		void setActive(bool active);

		HWND m_WindowHandle;

		int32 m_ConsoleHandle;

		bool m_IsInitialized;
		bool m_ShouldClose;
		bool m_IsActive;
		bool m_HasConsole;
//		bool m_IsFullScreen;
//		bool m_CanGoFullScreen;
	};
}
