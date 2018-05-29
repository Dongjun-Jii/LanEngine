#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include "../Scene/Scene.h"
#include "../Defines.h"
#include "../Component/Transform.h"

namespace Lan
{
	class Component;
	struct Context;
  
	class Object
	{
	public:
		Object();
		virtual ~Object();

		bool isActive() const;
		bool isVisible() const;

		Scene& getScene() const;

		Transform& getTransform();

		void setActive(bool active);
		void setVisible(bool visible);

	protected:
		virtual void onUpdate(Context& context) = 0;
		virtual void onDraw() {};

		template<typename T, typename... Args>
		void addComponent(Args&&... args);
		template<typename T>
		void removeComponent();
		template <typename T>
		T* getComponent();
		template <typename T>
		bool isComponentExist();

		void addChild(Object& object);
		void removeChild(Object& object);
		const std::set<Object*>& getChildren() const;
		bool isChildExist(Object& object);
		tsize getChildCount() const;

	private:
		enum class GarbageType
		{
			ComponentType,
			ObjectType
		};

		struct Garbage
		{
			Garbage(GarbageType type, void* element);
			GarbageType type;
			void* element;
		};

		void update(Context& context);
		void draw();

		void setScene(Scene* scene);
		void setParent(Object* object);

		void collectGarbage();

		bool m_IsActive;
		bool m_IsVisible;

		Scene* m_Scene;
		Object* m_Parent;

		std::map<tstring, Component *> m_Components;
		std::set<Object*> m_Children;
		std::vector<Garbage> m_GarbageCollector;

		friend void Scene::update(Context& context);
		friend void Scene::draw();

		friend class Component;
	};
}

#include "Object.inl"