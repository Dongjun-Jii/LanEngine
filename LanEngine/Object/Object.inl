#include "Object.h"
#include <typeinfo>
#include "../Utils/Utils.h"

namespace Lan
{
	template<typename T, typename... Args>
	T* Object::AddComponent(Args&&... args)
	{
		if (IsComponentExist<T>())
		{
			LOG(LogLevel::Warning, "있는 컴포넌트를 다시 추가하려고 시도함");
			return dynamic_cast<T *>(m_Components[typeid(T).name()]);
		}

		T* component = new T(this, args...);

		m_Components.insert(std::make_pair(typeid(T).name(), component));
		return component;
	}

	template <typename T>
	void Object::RemoveComponent()
	{
		if (Object::IsComponentExist<T>()) m_GarbageCollector.push_back(m_Components[typeid(T).name]);
		else LOG(LogLevel::Warning, "없는 컴포넌트를 삭제 시도함");
	}

	template <typename T>
	T* Object::GetComponent()
	{
		if (Object::IsComponentExist<T>()) return dynamic_cast<T*>(m_Components.at(typeid(T).name()));
		else LOG(LogLevel::Warning, "없는 컴포넌트를 검색 시도함");

		return nullptr;
	}

	template <typename T>
	bool Object::IsComponentExist()
	{
		if (m_Components.count(typeid(T).name()) > 0) return true;
		else return false;
	}

}