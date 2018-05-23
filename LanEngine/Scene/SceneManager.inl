#include "SceneManager.h"

namespace Lan
{
	template<typename T, typename... Args>
	bool SceneManager::addScene(tstring name, Args&&... args)
	{
		if (!isSceneExist(name))
		{
			Scene* scene = new T(args...);
			m_Scenes.insert(make_pair(name, scene));
			return true;
		}
		else
		{
			LOG(LogLevel::Warning, "이미 존재하는 Scene을 추가 시도");
			return false;
		}
	}
}