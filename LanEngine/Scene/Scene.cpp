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

	bool Scene::RemoveObject(Object& object)
	{
		if (IsObjectExist(object))
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

	bool Scene::IsObjectExist(Object& object)
	{
		return m_Objects.count(&object) > 0;
	}

	tsize Scene::GetObjectCount()
	{
		return m_Objects.size();
	}

	void Scene::Update(Context& context)
	{
		CollectGarbage();

		for (auto o : m_Objects)
		{
			if (o->IsActive()) 
			{
				o->Update(context);
			}
		}
		OnUpdate(context);
	}
	
	void Scene::Draw() 
	{
		for (auto o : m_Objects) 
		{
			if (o->IsVisible()) 
			{
				o->Draw();
			}
		}
		OnDraw();		//게임 프로그래머가 Draw시 해야 할 동작을 적으면 실행됨
	}

	void Scene::Pause()
	{
		m_IsPaused = true;
		OnPause();
	}

	void Scene::Start()
	{
		m_IsPaused = false;
		if (!m_HasStarted) m_HasStarted = true;
		else OnRestart();
		OnStart();
	}

	void Scene::CollectGarbage()
	{
		for (auto object : m_GarbageCollector)
		{
			if (!IsObjectExist(*object))
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