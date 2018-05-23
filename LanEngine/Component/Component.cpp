#include "Defines.h"
#include "Component.h"
#include "../Object/Object.h"

namespace Lan
{
	Component::Component() :
		m_Parent(nullptr)
	{

	}

	Component::~Component()
	{

	}

	Object& Component::getParent() const
	{
		return *(m_Parent);
	}

	void Component::update(Context& context)
	{
		onUpdate(context);
	}

	void Component::draw()
	{
		onDraw();
	}

	void Component::setParent(Object* obj)
	{
		m_Parent = obj;
	}
}