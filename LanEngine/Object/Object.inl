#include "Object.h"
#include <typeinfo>
#include "../Utils/Utils.h"

namespace Lan
{
	template<typename T, typename... Args>
	void Object::addComponent(Args&&... args)
	{
		if (m_Components.count(typeid(T).name()) > 0)
		{
			LOG(LogLevel::Warning, "있는 컴포넌트를 다시 추가하려고 시도함");
			return;
		}

		T* component = new T(args...);

		m_Components.insert(std::make_pair(typeid(T).name(), component));
		component->setParent(this);
	}

	template <typename T>
	void Object::removeComponent()
	{
		if (Object::isComponentExist<T>()) m_GarbageCollector.push_back(Garbage(GarbageType::ComponentType, static_cast<void *>(m_Components[typeid(T).name])));
		else LOG(LogLevel::Warning, "없는 컴포넌트를 삭제 시도함");
	}

	template <typename T>
	T* Object::getComponent()
	{
		if (Object::isComponentExist<T>()) return dynamic_cast<T*>(m_Components.at(typeid(T).name()));
		else LOG(LogLevel::Warning, "없는 컴포넌트를 검색 시도함");

		return nullptr;
	}

	template <typename T>
	bool Object::isComponentExist()
	{
		if (m_Components.count(typeid(T).name()) > 0) return true;
		else return false;
	}

}