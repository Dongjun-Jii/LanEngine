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
		bool addScene(tstring name, Args&&... args);
		bool removeScene(tstring name);

		Scene& getScene(tstring name);
		bool isSceneExist(tstring name);

		bool setCurrentScene(tstring name);
		Scene& getCurrentScene();

	private:
		SceneManager();
		virtual ~SceneManager();

		std::map<tstring, Scene*> m_Scenes;
		Scene* m_CurrentScene;
	};
}

#include "SceneManager.inl"