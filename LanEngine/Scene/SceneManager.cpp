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

	bool SceneManager::removeScene(tstring name)
	{
		if (isSceneExist(name) && m_CurrentScene != m_Scenes[name])
		{
			delete m_Scenes[name];
			m_Scenes.erase(name);
			return true;
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Scene을 삭제 시도");
			return false;
		}
		
	}

	Scene& SceneManager::getScene(tstring name)
	{
		if (isSceneExist(name))
		{
			return *m_Scenes[name];
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Scene을 Get 하려고 함");
			return *(reinterpret_cast<Scene*>(0));
		}
	}

	bool SceneManager::isSceneExist(tstring name)
	{
		return m_Scenes.count(name) > 0;
	}

	bool SceneManager::setCurrentScene(tstring name)
	{
		if (isSceneExist(name))
		{
			if (m_CurrentScene) m_CurrentScene->pause();
			m_CurrentScene = &getScene(name);
			m_CurrentScene->start();
			return true;
		}
		else
		{
			return false;
		}
	}
	
	Scene& SceneManager::getCurrentScene()
	{
		return *m_CurrentScene;
	}
}