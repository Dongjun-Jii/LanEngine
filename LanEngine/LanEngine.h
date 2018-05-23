#pragma once
#include "Defines.h"
#include "Utils/Utils.h"
#include "Windows/Window.h"
#include "Input/Input.h"
#include "BaseGame.h"
#include "Scene/SceneManager.h"
#include "Graphics/GraphicsManager.h"
#include "Graphics/ShaderManager.h"
#include "Object/Object.h"
#include "Resource/ResourceManager.h"

#ifdef USE_CONSOLE
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#endif

namespace Lan
{
	class LanEngine final : public Singleton<LanEngine>
	{
	public:
		friend Singleton<LanEngine>;

		void initialize(HINSTANCE instanceHandle, ivec2 windowSize, BaseGame& game);

		void run();

	private:
		LanEngine();
		~LanEngine();

		void update();
		void draw();

		Logger* m_Logger;
		Window* m_Window;
		Input* m_Input;
		BaseGame* m_Game;
		SceneManager* m_SceneManager;
		GraphicsManager* m_Graphics;
		ResourceManager* m_Resource;
	};
}