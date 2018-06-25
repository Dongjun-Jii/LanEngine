#include "Defines.h"
#include "Window.h"
#include "../Utils/Utils.h"
#include <io.h>
#include <fcntl.h>

namespace Lan
{
	Window::Window() :
		m_WindowHandle(nullptr),
		m_IsInitialized(false),
		m_ShouldClose(false),
		m_IsActive(false)
//		m_IsFullScreen(false),
//		m_CanGoFullScreen(false)
	{

	}

	Window::~Window()
	{

	}

	void Window::Initialize(HINSTANCE instanceHandle, ivec2 size)
	{
		if (m_IsInitialized)
		{
			LOG(LogLevel::Warning, "윈도우 객체 중복 초기화 시도");
			return;
		}

		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = instanceHandle;
		wc.lpfnWndProc = Window::WndProc;
		wc.lpszClassName = L"LanEngine";
		wc.lpszMenuName = L"Menu";
		wc.style = CS_HREDRAW | CS_VREDRAW;

		if (!RegisterClass(&wc))
		{
			throw std::runtime_error("Window class registration Failed");
		}

		m_WindowHandle = CreateWindow(L"LanEngine", L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y, 0, 0, instanceHandle, 0);

		if (!m_WindowHandle)
		{
			throw std::runtime_error("CreateWindow Failed");
		}

		ShowWindow(m_WindowHandle, SW_SHOWNORMAL);
		UpdateWindow(m_WindowHandle);
	}

	void Window::Update()
	{
		MSG msg = {};
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				m_ShouldClose = true;
			}
		}
	}

	const HWND& Window::GetHandle() const
	{
		return m_WindowHandle;
	}

	bool Window::ShouldClose() const
	{
		return m_ShouldClose;
	}

	bool Window::IsActive() const
	{
		return m_IsActive;
	}

	void Window::SetActive(bool active)
	{
		m_IsActive = active;
	}

	bool Window::SetWindowName(tstring windowName) const
	{
		return SetWindowTextA(m_WindowHandle, windowName.c_str()) != false;
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_ENTERSIZEMOVE:
			case WM_NCRBUTTONDOWN:
				Window::GetInstance().SetActive(false);
				break;
			case WM_EXITSIZEMOVE:
			case WM_EXITMENULOOP:
				Window::GetInstance().SetActive(true);
				break;
			case WM_LBUTTONDOWN:
				Input::GetInstance().SetMouseState(MouseButton::Left, true); break;
			case WM_LBUTTONUP:
				Input::GetInstance().SetMouseState(MouseButton::Left, false); break;
			case WM_RBUTTONDOWN:
				Input::GetInstance().SetMouseState(MouseButton::Right, true); break;
			case WM_RBUTTONUP:
				Input::GetInstance().SetMouseState(MouseButton::Right, false); break;
			case WM_SYSCOMMAND:
				//SC_KEYMENU == (wParam & 0xFFF0)

				//alt+enter 전체화면
				//Input 구현 후 상호작용
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}