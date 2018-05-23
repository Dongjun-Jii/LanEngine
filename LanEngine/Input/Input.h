#pragma once
#include "../Utils/Utils.h"

namespace Lan
{
	class Window;

	using Key = char;

	enum class MouseButton
	{
		Left,
		Right
	};

	class Input final : public Singleton<Input>
	{
	public:
		friend Singleton<Input>;

		void update();

		//눌려있다면 true, 그외엔 false
		bool isKeyDown(Key key) const;
		//해당 키를 누른 첫 프레임에만 true, 그외엔 false
		bool isKeyPressed(Key key) const;
		//해당 키를 뗀 첫 프레임에만 true, 그외엔 false
		bool isKeyReleased(Key key) const;

		//눌려있다면 true, 그외엔 false
		bool isButtonDown(MouseButton button) const;
		//해당 버튼을 누른 첫 프레임에만 true, 그외엔 false
		bool isButtonPressed(MouseButton button) const;
		//해당 버튼을 뗀 첫 프레임에만 true, 그외엔 false
		bool isButtonReleased(MouseButton button) const;

		//마우스 커서 위치
		ivec2 getCursorPos() const;
	private:
		static const int KEY_COUNT = 256;
		static const int KEY_ID_MIN = 0x07;
		static const int KEY_ID_MAX = 0xfe;

	private:
		Input();
		~Input();

		void updateKeyState();
		void updateMouseState();

		void setMouseState(MouseButton button, bool isDown);

		BYTE* m_CurKeyState;
		BYTE* m_PreKeyState;

		bool m_CurMouseState[2];
		bool m_PreMouseState[2];

		friend class Window;
	};
}