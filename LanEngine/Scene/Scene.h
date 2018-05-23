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

	protected:
		virtual void onStart() {};
		virtual void onUpdate(Context& context) = 0;
		virtual void onDraw() {};
		virtual void onPause() {};

		virtual void onRestart() {};

		template<typename T, typename... Args>
		Object& addObject(Args&&... args);
		bool removeObject(Object& object);
		bool isObjectExist(Object& object);

		int getObjectCount();

		void collectGarbage();

	private:
		void update(Context& context);
		void draw();
		void pause();
		void start();

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
