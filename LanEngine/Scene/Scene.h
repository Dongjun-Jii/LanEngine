#pragma once
#include "../Defines.h"

namespace Lan
{
	class Object;
	class LanEngine;
	class SceneManager;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		template<typename T, typename... Args>
		Object& AddObject(Args&&... args);
		bool RemoveObject(Object& object);
		bool IsObjectExist(Object& object);

		tsize GetObjectCount();

	protected:
		virtual void OnStart() {};
		virtual void OnUpdate(Context& context) = 0;
		virtual void OnDraw() {};
		virtual void OnPause() {};

		virtual void OnRestart() {};

		void CollectGarbage();

	private:
		void Update(Context& context);
		void Draw();
		void Pause();
		void Start();

		std::set<Object*> m_Objects;
		std::vector<Object*> m_GarbageCollector;

		bool m_IsPaused;
		bool m_HasStarted;

		friend LanEngine;
		friend Object;
		friend SceneManager;
	};
}

#include "Scene.inl"
