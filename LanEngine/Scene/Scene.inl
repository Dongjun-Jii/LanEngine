#include "Scene.h"

namespace Lan
{
	template<typename T, typename... Args>
	Object& Scene::AddObject(Args&&...args)
	{
		Object* obj = new T(args...);
		m_Objects.insert(obj);
		return *obj;
	}
}