#include "Defines.h"
#include "Scene.h"
#include "../Object/Object.h"
#include "../Utils/Logger.h"

namespace Lan
{
	Scene::Scene() : 
		m_IsPaused(false),
		m_HasStarted(false)
	{
		
	}

	Scene::~Scene()
	{
		m_Objects.clear();
		m_GarbageCollector.clear();
	}

	bool Scene::removeObject(Object& object)
	{
		if (isObjectExist(object))
		{
			m_GarbageCollector.push_back(&object);
			return true;
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Object를 삭제 시도");
			return false;
		}
	}

	bool Scene::isObjectExist(Object& object)
	{
		return m_Objects.count(&object) > 0;
	}

	int Scene::getObjectCount()
	{
		return (int32) m_Objects.size();
	}

	void Scene::update(Context& context)
	{
		collectGarbage();

		for (auto o : m_Objects)
		{
			if (o->isActive()) 
			{
				o->update(context);
			}
		}
		onUpdate(context);
	}
	
	void Scene::draw() 
	{
		for (auto o : m_Objects) 
		{
			if (o->isVisible()) 
			{
				o->draw();
			}
		}
		onDraw();		//게임 프로그래머가 draw시 해야 할 동작을 적으면 실행됨
	}

	void Scene::pause()
	{
		m_IsPaused = true;
		onPause();
	}

	void Scene::start()
	{
		m_IsPaused = false;
		if (!m_HasStarted) m_HasStarted = true;
		else onRestart();
		onStart();
	}

	void Scene::collectGarbage()
	{
		for (auto object : m_GarbageCollector)
		{
			if (!isObjectExist(*object))
			{
				LOG(LogLevel::Error, "오브젝트 제거 오류");
				break;
			}
			m_Objects.erase(object);
			delete object;
		}
		m_GarbageCollector.clear();
	}
}