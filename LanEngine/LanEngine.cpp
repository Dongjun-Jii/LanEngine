#include "Defines.h"
#include "LanEngine.h"
#include "Resource/Texture.h"

namespace Lan
{
	LanEngine::LanEngine()
	{
		
	}

	void LanEngine::initialize(HINSTANCE instanceHandle, ivec2 windowSize, BaseGame& game)
	{
		Logger::createInstance();
		Logger::getInstance().initialize(true);

		Window::createInstance();
		Input::createInstance();
		SceneManager::createInstance();
		GraphicsManager::createInstance();
		ResourceManager::createInstance();
		
		Window::getInstance().initialize(instanceHandle, windowSize);

		GraphicsManager::getInstance().initialize(Window::getInstance().getHandle(), windowSize, false);

		ShaderManager::createInstance();

		m_Logger = &Logger::getInstance();
		m_Window = &Window::getInstance();
		m_Input = &Input::getInstance();
		m_SceneManager = &SceneManager::getInstance();
		m_Graphics = &GraphicsManager::getInstance();
		m_Resource = &ResourceManager::getInstance();
		m_Game = &game;

		ResourceFactory<Texture>::createInstance();
		m_Resource->addResourceType("png", ResourceFactory<Texture>::getInstance());

		m_Game->initialize();
	}

	LanEngine::~LanEngine()
	{
		m_Game->destroy();
		ResourceManager::destroyInstance();
		ShaderManager::destroyInstance();
		GraphicsManager::destroyInstance();
		SceneManager::destroyInstance();
		Input::destroyInstance();
		Window::destroyInstance();
		Logger::destroyInstance();
	}

	void LanEngine::run()
	{
		bool isRunning = true;
		
		while (isRunning)
		{
			update();

			draw();


			if (m_Window->shouldClose())
			{
				isRunning = false;
			}
		}
	}

	void LanEngine::update()
	{
		Context context;
		context.deltaTime = 1 / 60.0f;


		m_Input->update();
		m_Window->peekMessage();

		m_Game->update(context);

		Scene& scene = m_SceneManager->getCurrentScene();
		scene.update(context);

	}

	void LanEngine::draw()
	{
		m_Graphics->beginDraw();

		Scene& scene = m_SceneManager->getCurrentScene();
		scene.draw();

		m_Graphics->endDraw();
	}
}