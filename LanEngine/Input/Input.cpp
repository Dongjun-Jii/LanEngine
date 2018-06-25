#include "Defines.h"
#include "Input.h"
#include "../Windows/Window.h"

namespace Lan
{
	Input::Input() :
		m_CurKeyState(new BYTE[KEY_COUNT]),
		m_PreKeyState(new BYTE[KEY_COUNT])
	{

	}

	Input::~Input()
	{
		if (m_CurKeyState)
		{
			delete[] m_CurKeyState;
		}

		if (m_PreKeyState)
		{
			delete[] m_PreKeyState;
		}
	}

	void Input::Update()
	{
		UpdateKeyState();
		UpdateMouseState();
	}

	void Input::UpdateKeyState()
	{
		//현재 상태를 이전 프레임의 상태로 변환
		BYTE* temp = m_PreKeyState;
		m_PreKeyState = m_CurKeyState;
		m_CurKeyState = temp;

		//현재 프레임의 키보드 상태 확인
		if (!GetKeyboardState(m_CurKeyState))
		{
			LOG(LogLevel::Error, "키보드 입력 오류");
		}
	}

	void Input::UpdateMouseState()
	{
		//현재 상태를 이전 프레임의 상태로 변환
		m_PreKeyState[0] = m_CurMouseState[0];
		m_PreKeyState[1] = m_CurMouseState[1];
	}

	void Input::SetMouseState(MouseButton button, bool isDown)
	{
		switch (button)
		{
		case MouseButton::Left:
			m_CurMouseState[0] = isDown;
			break;
		case MouseButton::Right:
			m_CurMouseState[1] = isDown;
			break;
		}
	}


	bool Input::IsKeyDown(Key key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "잘못된 키보드 키값 체크");
			return false;
		}

		return m_CurKeyState[key] & 0xf0;
	}

	bool Input::IsKeyPressed(Key key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "잘못된 키보드 키값 체크");
			return false;
		}

		if (!(m_PreKeyState[key] & 0xf0) && (m_CurKeyState[key] & 0xf0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Input::IsKeyReleased(Key key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "잘못된 키보드 키값 체크");
			return false;
		}

		if ((m_PreKeyState[key] & 0xf0) && !(m_CurKeyState[key] & 0xf0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Input::IsButtonDown(MouseButton button) const
	{
		switch (button)
		{
			case MouseButton::Left:
				return m_CurMouseState[0];
			case MouseButton::Right:
				return m_CurMouseState[1];
		}
		return false;
	}

	bool Input::IsButtonPressed(MouseButton button) const
	{
		switch (button)
		{
		case MouseButton::Left:
			return !m_PreMouseState[0] && m_CurMouseState[0];
		case MouseButton::Right:
			return !m_PreMouseState[1] && m_CurMouseState[1];
		}
		return false;
	}

	bool Input::IsButtonReleased(MouseButton button) const
	{
		switch (button)
		{
		case MouseButton::Left:
			return m_PreMouseState[0] && !m_CurMouseState[0];
		case MouseButton::Right:
			return m_PreMouseState[1] && !m_CurMouseState[1];
		}
		return false;
	}

	ivec2 Input::GetCursorPos() const
	{
		POINT cursorPos;
		if (!::GetCursorPos(&cursorPos))
		{
			LOG(LogLevel::Error, "커서 위치 참고 오류");
		}

		ScreenToClient(Window::GetInstance().GetHandle(), &cursorPos);

		return { cursorPos.x, cursorPos.y };
	}
}