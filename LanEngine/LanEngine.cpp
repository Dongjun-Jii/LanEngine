#include "Defines.h"
#include "LanEngine.h"
#include "Resource/Texture.h"

namespace Lan
{
	LanEngine::LanEngine()
	{
		
	}

	void LanEngine::Initialize(HINSTANCE instanceHandle, ivec2 windowSize, BaseGame& game)
	{
		Logger::CreateInstance();
		Logger::GetInstance().Initialize(true);

		Window::CreateInstance();
		Input::CreateInstance();
		SceneManager::CreateInstance();
		GraphicsManager::CreateInstance();
		ResourceManager::CreateInstance();
		
		Window::GetInstance().Initialize(instanceHandle, windowSize);

		GraphicsManager::GetInstance().Initialize(Window::GetInstance().GetHandle(), windowSize, false);

		ShaderManager::CreateInstance();

		m_Logger = &Logger::GetInstance();
		m_Window = &Window::GetInstance();
		m_Input = &Input::GetInstance();
		m_SceneManager = &SceneManager::GetInstance();
		m_Graphics = &GraphicsManager::GetInstance();
		m_Resource = &ResourceManager::GetInstance();
		m_Game = &game;

		ResourceFactory<Texture>::CreateInstance();
		m_Resource->AddResourceType("png", ResourceFactory<Texture>::GetInstance());

		m_Game->Initialize();
	}

	LanEngine::~LanEngine()
	{
		m_Game->Destroy();
		ResourceManager::DestroyInstance();
		ShaderManager::DestroyInstance();
		GraphicsManager::DestroyInstance();
		SceneManager::DestroyInstance();
		Input::DestroyInstance();
		Window::DestroyInstance();
		Logger::DestroyInstance();
	}

	void LanEngine::Run()
	{
		bool isRunning = true;
		
		while (isRunning)
		{
			Update();

			Draw();


			if (m_Window->ShouldClose())
			{
				isRunning = false;
			}
		}
	}

	void LanEngine::Update()
	{
		Context context;
		context.deltaTime = 1 / 60.0f;


		m_Input->Update();
		m_Window->Update();

		m_Game->Update(context);

		Scene& scene = m_SceneManager->GetCurrentScene();
		scene.Update(context);

	}

	void LanEngine::Draw()
	{
		m_Graphics->BeginDraw();

		Scene& scene = m_SceneManager->GetCurrentScene();
		scene.Draw();

		m_Graphics->EndDraw();
	}
}