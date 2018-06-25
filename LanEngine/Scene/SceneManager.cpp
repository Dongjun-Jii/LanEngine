#include "Defines.h"
#include "SceneManager.h"
#include <utility>
#include "../Utils/Logger.h"
#include "Scene.h"

namespace Lan
{
	SceneManager::SceneManager() :
		m_CurrentScene(nullptr)
	{

	}

	SceneManager::~SceneManager()
	{

	}

	bool SceneManager::RemoveScene(tstring name)
	{
		if (IsSceneExist(name) && m_CurrentScene != m_Scenes[name])
		{
			delete m_Scenes[name];
			m_Scenes.erase(name);
			return true;
		}
		else if (m_CurrentScene == m_Scenes[name])
		{
			LOG(LogLevel::Warning, "현재 씬을 삭제하려 시도");
			return false;
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Scene을 삭제 시도");
			return false;
		}
		
	}

	Scene* SceneManager::GetScene(tstring name)
	{
		if (IsSceneExist(name))
		{
			return m_Scenes[name];
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Scene을 Get 하려고 함");
			return nullptr;
		}
	}

	bool SceneManager::IsSceneExist(tstring name)
	{
		return m_Scenes.count(name) > 0;
	}

	bool SceneManager::SetCurrentScene(tstring name)
	{
		if (IsSceneExist(name))
		{
			if (m_CurrentScene) m_CurrentScene->Pause();
			m_CurrentScene = GetScene(name);
			m_CurrentScene->Start();
			return true;
		}
		else
		{
			return false;
		}
	}
	
	Scene& SceneManager::GetCurrentScene()
	{
		return *m_CurrentScene;
	}
}