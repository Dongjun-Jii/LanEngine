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

		bool IsActive() const;
		bool IsVisible() const;

		Scene& GetScene() const;

		Transform& GetTransform();

		void SetActive(bool active);
		void SetVisible(bool visible);

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);
		template<typename T>
		void RemoveComponent();
		template <typename T>
		T* GetComponent();
		template <typename T>
		bool IsComponentExist();

		void AddChild(Object& object);
		void RemoveChild(Object& object);
		const std::set<Object*>& GetChildren() const;
		bool IsChildExist(Object& object);
		tsize GetChildCount() const;

		void SetParent(Object* object);
		Object* GetParent() const;

	protected:
		virtual void OnUpdate(Context& context) = 0;
		virtual void OnDraw() {};


	private:

		void Update(Context& context);
		void Draw();

		void SetScene(Scene* scene);

		void CollectGarbage();

		bool m_IsActive;
		bool m_IsVisible;

		Scene* m_Scene;
		Object* m_Parent;

		std::map<tstring, Component *> m_Components;
		std::set<Object*> m_Children;
		std::vector<Component*> m_GarbageCollector;

		friend void Scene::Update(Context& context);
		friend void Scene::Draw();

		friend class Component;
	};
}

#include "Object.inl"