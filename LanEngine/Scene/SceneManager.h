#pragma once
#include <map>
#include "../Utils/Utils.h"
#include "Scene.h"
#include "../Defines.h"

namespace Lan
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		friend Singleton<SceneManager>;
		
		template<typename T, typename... Args>
		bool AddScene(tstring name, Args&&... args);
		bool RemoveScene(tstring name);

		Scene* GetScene(tstring name);
		bool IsSceneExist(tstring name);

		bool SetCurrentScene(tstring name);
		Scene& GetCurrentScene();

	private:
		SceneManager();
		virtual ~SceneManager();

		std::map<tstring, Scene*> m_Scenes;
		Scene* m_CurrentScene;
	};
}

#include "SceneManager.inl"