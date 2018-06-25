#include "Defines.h"
#include "Object.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"
#include <utility>
#include <map>
#include <iterator>
#include "../Graphics/GraphicsManager.h"

using namespace std;

namespace Lan
{
	Object::Object():
		m_IsActive(true),
		m_IsVisible(true),
		m_Scene(nullptr),
		m_Parent(nullptr)
	{
		AddComponent<Transform>();
	}

	Object::~Object()
	{
		for (Object* o : m_Children)
		{
			o->m_Parent = nullptr;
		}
		m_Children.clear();

		if (m_Parent)
		{
			m_Parent->m_Children.erase(this);
		}

		auto it = m_Components.begin();
		for(; it != m_Components.end(); it++)
		{
			delete it->second;
		}
		m_Components.clear();

	}

	bool Object::IsActive() const
	{
		return m_IsActive;
	}

	bool Object::IsVisible() const
	{
		return m_IsVisible;
	}

	Scene& Object::GetScene() const
	{
		return *m_Scene;
	}

	void Object::Update(Context& context)
	{
		CollectGarbage();

		if (!m_IsActive) return;

		OnUpdate(context);

		for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
		{
			iter->second->Update(context);
		}

		for (Object* child : m_Children)
		{
			child->Update(context);
		}
	}

	void Object::Draw()
	{
		if (!m_IsVisible) return;

		ID3D11DeviceContext * deviceContext = GraphicsManager::GetInstance().GetDeviceContext();

		OnDraw();

		for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
		{
			iter->second->Draw();
		}

		deviceContext->DrawIndexed(6, 0, 0);

		for (Object* child : m_Children)
		{
			child->Draw();
		}
	}

	Transform& Object::GetTransform()
	{
		return *(GetComponent<Transform>());
	}

	void Object::AddChild(Object& object)
	{
		if (m_Children.count(&object) > 0)
		{
			LOG(LogLevel::Warning, "있는 차일드를 다시 추가하려고 시도함");
			return;
		}

		m_Children.insert(&object);
		object.SetParent(this);
	}

	void Object::RemoveChild(Object& object)
	{
		if (m_Children.count(&object) < 1)
		{
			LOG(LogLevel::Warning, "없는 차일드를 삭제하려고 시도함");
			return;
		}

		object.m_Parent = nullptr;
		m_Children.erase(&object);
	}

	const std::set<Object*>& Object::GetChildren() const
	{
		return m_Children;
	}

	bool Object::IsChildExist(Object& object)
	{
		if (m_Children.count(&object) > 0) return true;
		else return false;
	}

	void Object::SetActive(bool active)
	{
		m_IsActive = active;
	}

	void Object::SetVisible(bool visible)
	{
		m_IsVisible = visible;
	}

	void Object::SetScene(Scene* scene)
	{
		m_Scene = scene;
	}

	void Object::SetParent(Object* object)
	{
		if (m_Parent)
		{
			m_Parent->RemoveChild(*this);
		}

		if (object)
		{
			m_Parent = object;
			if (!m_Parent->IsChildExist(*this))
			{
				m_Parent->m_Children.insert(this);
			}
		}
		
	}

	Object* Object::GetParent() const
	{
		if (m_Parent)
		{
			return m_Parent;
		}
		else
		{
			return nullptr;
		}
	}

	tsize Object::GetChildCount() const
	{
		return m_Children.size();
	}

	void Object::CollectGarbage()
	{
		for (Component* component : m_GarbageCollector)
		{
			if (m_Components.count(typeid(*component).name()) < 1)
			{
				LOG(LogLevel::Error, "컴포넌트제거 오류");
				break;
			}

			m_Components.erase(typeid(*component).name());
			delete component;
		}

		m_GarbageCollector.clear();
	}

}